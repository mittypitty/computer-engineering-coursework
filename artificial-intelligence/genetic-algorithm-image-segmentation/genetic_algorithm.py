"""
Genetic Algorithm Implementation for Segmentation Optimization

This module implements the complete GA with:
1. Population initialization
2. Selection methods (Tournament, Roulette Wheel)
3. Crossover operators (Single-point, Two-point, Uniform, Blend/BLX-alpha)
4. Mutation operators (Gaussian, Uniform)
5. Elitism
6. Evolution loop with early stopping
"""

import numpy as np
from typing import List, Tuple, Callable, Optional
import random
from dataclasses import dataclass
import copy

from genome import Genome, HSVThreshold
from fitness import FitnessEvaluator
from config import GA_CONFIG, HSV_BOUNDS, MULTI_MASK_CONFIG


@dataclass
class EvolutionStats:
    """Statistics for a single generation."""
    generation: int
    best_fitness: float
    avg_fitness: float
    worst_fitness: float
    best_genome: Genome


class GeneticAlgorithm:
    """
    Genetic Algorithm for optimizing HSV segmentation parameters.
    """
    
    def __init__(self, config: dict = None):
        """
        Initialize the Genetic Algorithm.
        
        Args:
            config: GA configuration dictionary
        """
        self.config = config or GA_CONFIG
        
        # Set random seed for reproducibility
        seed = self.config.get('random_seed', 42)
        np.random.seed(seed)
        random.seed(seed)
        
        # Initialize parameters
        self.population_size = self.config.get('population_size', 100)
        self.num_generations = self.config.get('num_generations', 50)
        self.elite_size = self.config.get('elite_size', 5)
        self.tournament_size = self.config.get('tournament_size', 5)
        self.crossover_rate = self.config.get('crossover_rate', 0.8)
        self.crossover_type = self.config.get('crossover_type', 'blend')
        self.blend_alpha = self.config.get('blend_alpha', 0.5)
        self.mutation_rate = self.config.get('mutation_rate', 0.15)
        self.mutation_sigma = self.config.get('mutation_sigma', 10)
        self.early_stopping = self.config.get('early_stopping_generations', 10)
        self.fitness_threshold = self.config.get('fitness_threshold', 0.95)
        
        # Evolution history
        self.history: List[EvolutionStats] = []
        self.best_genome: Optional[Genome] = None
        
        # Fitness evaluator
        self.evaluator = FitnessEvaluator()
    
    def initialize_population(self, smart_init: bool = True) -> List[Genome]:
        """
        Create initial population.
        
        Args:
            smart_init: If True, use red-object initialization for some individuals
            
        Returns:
            List of initial genomes
        """
        population = []
        
        if smart_init:
            # 30% initialized for red objects (pomegranate prior knowledge)
            num_smart = int(0.3 * self.population_size)
            for _ in range(num_smart):
                population.append(Genome.create_for_red_objects())
            
            # 70% random initialization for diversity
            for _ in range(self.population_size - num_smart):
                population.append(Genome.create_random())
        else:
            for _ in range(self.population_size):
                population.append(Genome.create_random())
        
        return population
    
    # =========================================================================
    # SELECTION OPERATORS
    # =========================================================================
    
    def tournament_selection(self, population: List[Genome]) -> Genome:
        """
        Tournament selection: Select the best individual from a random tournament.
        
        Args:
            population: Current population
            
        Returns:
            Selected genome
        """
        tournament = random.sample(population, min(self.tournament_size, len(population)))
        winner = max(tournament, key=lambda g: g.fitness)
        return winner.copy()
    
    def roulette_wheel_selection(self, population: List[Genome]) -> Genome:
        """
        Roulette wheel (fitness proportionate) selection.
        
        Args:
            population: Current population
            
        Returns:
            Selected genome
        """
        total_fitness = sum(g.fitness for g in population)
        if total_fitness == 0:
            return random.choice(population).copy()
        
        pick = random.uniform(0, total_fitness)
        current = 0
        for genome in population:
            current += genome.fitness
            if current >= pick:
                return genome.copy()
        
        return population[-1].copy()
    
    def select_parents(self, population: List[Genome]) -> Tuple[Genome, Genome]:
        """
        Select two parents for reproduction.
        
        Args:
            population: Current population
            
        Returns:
            Two parent genomes
        """
        parent1 = self.tournament_selection(population)
        parent2 = self.tournament_selection(population)
        return parent1, parent2
    
    # =========================================================================
    # CROSSOVER OPERATORS
    # =========================================================================
    
    def single_point_crossover(self, parent1: Genome, parent2: Genome) -> Tuple[Genome, Genome]:
        """
        Single-point crossover.
        
        Args:
            parent1, parent2: Parent genomes
            
        Returns:
            Two offspring genomes
        """
        if random.random() > self.crossover_rate:
            return parent1.copy(), parent2.copy()
        
        arr1 = parent1.to_array()
        arr2 = parent2.to_array()
        
        point = random.randint(1, len(arr1) - 1)
        
        child1_arr = np.concatenate([arr1[:point], arr2[point:]])
        child2_arr = np.concatenate([arr2[:point], arr1[point:]])
        
        child1 = Genome.from_array(child1_arr)
        child2 = Genome.from_array(child2_arr)
        
        return child1, child2
    
    def two_point_crossover(self, parent1: Genome, parent2: Genome) -> Tuple[Genome, Genome]:
        """
        Two-point crossover.
        
        Args:
            parent1, parent2: Parent genomes
            
        Returns:
            Two offspring genomes
        """
        if random.random() > self.crossover_rate:
            return parent1.copy(), parent2.copy()
        
        arr1 = parent1.to_array()
        arr2 = parent2.to_array()
        
        points = sorted(random.sample(range(1, len(arr1)), 2))
        
        child1_arr = np.concatenate([arr1[:points[0]], arr2[points[0]:points[1]], arr1[points[1]:]])
        child2_arr = np.concatenate([arr2[:points[0]], arr1[points[0]:points[1]], arr2[points[1]:]])
        
        child1 = Genome.from_array(child1_arr)
        child2 = Genome.from_array(child2_arr)
        
        return child1, child2
    
    def uniform_crossover(self, parent1: Genome, parent2: Genome) -> Tuple[Genome, Genome]:
        """
        Uniform crossover: Each gene is randomly selected from either parent.
        
        Args:
            parent1, parent2: Parent genomes
            
        Returns:
            Two offspring genomes
        """
        if random.random() > self.crossover_rate:
            return parent1.copy(), parent2.copy()
        
        arr1 = parent1.to_array()
        arr2 = parent2.to_array()
        
        mask = np.random.random(len(arr1)) < 0.5
        
        child1_arr = np.where(mask, arr1, arr2)
        child2_arr = np.where(mask, arr2, arr1)
        
        child1 = Genome.from_array(child1_arr)
        child2 = Genome.from_array(child2_arr)
        
        return child1, child2
    
    def blend_crossover(self, parent1: Genome, parent2: Genome) -> Tuple[Genome, Genome]:
        """
        BLX-alpha (Blend Crossover): Creates offspring in an extended range
        between parents, allowing exploration beyond parent values.
        
        For each gene, the offspring value is sampled from:
        [min(p1,p2) - alpha*d, max(p1,p2) + alpha*d]
        where d = |p1 - p2|
        
        Args:
            parent1, parent2: Parent genomes
            
        Returns:
            Two offspring genomes
        """
        if random.random() > self.crossover_rate:
            return parent1.copy(), parent2.copy()
        
        arr1 = parent1.to_array().astype(np.float64)
        arr2 = parent2.to_array().astype(np.float64)
        
        alpha = self.blend_alpha
        
        child1_arr = np.zeros_like(arr1)
        child2_arr = np.zeros_like(arr2)
        
        for i in range(len(arr1)):
            min_val = min(arr1[i], arr2[i])
            max_val = max(arr1[i], arr2[i])
            d = max_val - min_val
            
            low = min_val - alpha * d
            high = max_val + alpha * d
            
            child1_arr[i] = np.random.uniform(low, high)
            child2_arr[i] = np.random.uniform(low, high)
        
        # Clip to valid ranges
        child1_arr = np.clip(child1_arr, 0, 255).astype(np.int32)
        child2_arr = np.clip(child2_arr, 0, 255).astype(np.int32)
        
        # Handle H channel bounds (0-179)
        num_masks = len(parent1.thresholds)
        for m in range(num_masks):
            base = m * 6
            child1_arr[base:base+2] = np.clip(child1_arr[base:base+2], 0, 179)
            child2_arr[base:base+2] = np.clip(child2_arr[base:base+2], 0, 179)
        
        child1 = Genome.from_array(child1_arr)
        child2 = Genome.from_array(child2_arr)
        
        return child1, child2
    
    def crossover(self, parent1: Genome, parent2: Genome) -> Tuple[Genome, Genome]:
        """
        Apply crossover based on configured type.
        
        Args:
            parent1, parent2: Parent genomes
            
        Returns:
            Two offspring genomes
        """
        if self.crossover_type == 'single_point':
            return self.single_point_crossover(parent1, parent2)
        elif self.crossover_type == 'two_point':
            return self.two_point_crossover(parent1, parent2)
        elif self.crossover_type == 'uniform':
            return self.uniform_crossover(parent1, parent2)
        elif self.crossover_type == 'blend':
            return self.blend_crossover(parent1, parent2)
        else:
            return self.blend_crossover(parent1, parent2)
    
    # =========================================================================
    # MUTATION OPERATORS
    # =========================================================================
    
    def gaussian_mutation(self, genome: Genome) -> Genome:
        """
        Gaussian mutation: Add Gaussian noise to each gene with probability mutation_rate.
        
        Args:
            genome: Genome to mutate
            
        Returns:
            Mutated genome
        """
        mutant = genome.copy()
        
        for threshold in mutant.thresholds:
            if random.random() < self.mutation_rate:
                threshold.h_low = int(np.clip(
                    threshold.h_low + np.random.normal(0, self.mutation_sigma),
                    0, 179
                ))
            if random.random() < self.mutation_rate:
                threshold.h_high = int(np.clip(
                    threshold.h_high + np.random.normal(0, self.mutation_sigma),
                    0, 179
                ))
            if random.random() < self.mutation_rate:
                threshold.s_low = int(np.clip(
                    threshold.s_low + np.random.normal(0, self.mutation_sigma),
                    0, 255
                ))
            if random.random() < self.mutation_rate:
                threshold.s_high = int(np.clip(
                    threshold.s_high + np.random.normal(0, self.mutation_sigma),
                    0, 255
                ))
            if random.random() < self.mutation_rate:
                threshold.v_low = int(np.clip(
                    threshold.v_low + np.random.normal(0, self.mutation_sigma),
                    0, 255
                ))
            if random.random() < self.mutation_rate:
                threshold.v_high = int(np.clip(
                    threshold.v_high + np.random.normal(0, self.mutation_sigma),
                    0, 255
                ))
            
            threshold.validate_and_fix()
        
        return mutant
    
    def uniform_mutation(self, genome: Genome) -> Genome:
        """
        Uniform mutation: Replace gene with random value with probability mutation_rate.
        
        Args:
            genome: Genome to mutate
            
        Returns:
            Mutated genome
        """
        mutant = genome.copy()
        
        for threshold in mutant.thresholds:
            if random.random() < self.mutation_rate:
                threshold.h_low = np.random.randint(0, 180)
            if random.random() < self.mutation_rate:
                threshold.h_high = np.random.randint(0, 180)
            if random.random() < self.mutation_rate:
                threshold.s_low = np.random.randint(0, 256)
            if random.random() < self.mutation_rate:
                threshold.s_high = np.random.randint(0, 256)
            if random.random() < self.mutation_rate:
                threshold.v_low = np.random.randint(0, 256)
            if random.random() < self.mutation_rate:
                threshold.v_high = np.random.randint(0, 256)
            
            threshold.validate_and_fix()
        
        return mutant
    
    def mutate(self, genome: Genome) -> Genome:
        """
        Apply mutation to genome.
        
        Args:
            genome: Genome to mutate
            
        Returns:
            Mutated genome
        """
        return self.gaussian_mutation(genome)
    
    # =========================================================================
    # EVOLUTION
    # =========================================================================
    
    def get_elites(self, population: List[Genome]) -> List[Genome]:
        """
        Get the best individuals for elitism.
        
        Args:
            population: Current population
            
        Returns:
            List of elite genomes
        """
        sorted_pop = sorted(population, key=lambda g: g.fitness, reverse=True)
        return [g.copy() for g in sorted_pop[:self.elite_size]]
    
    def create_next_generation(self, population: List[Genome]) -> List[Genome]:
        """
        Create the next generation through selection, crossover, and mutation.
        
        Args:
            population: Current population
            
        Returns:
            New population
        """
        new_population = []
        
        # Elitism: Keep best individuals
        elites = self.get_elites(population)
        new_population.extend(elites)
        
        # Fill rest of population with offspring
        while len(new_population) < self.population_size:
            parent1, parent2 = self.select_parents(population)
            child1, child2 = self.crossover(parent1, parent2)
            child1 = self.mutate(child1)
            child2 = self.mutate(child2)
            
            new_population.append(child1)
            if len(new_population) < self.population_size:
                new_population.append(child2)
        
        return new_population
    
    def evolve(self, images: List[np.ndarray], 
               ground_truths: List[np.ndarray],
               verbose: bool = True) -> Genome:
        """
        Run the genetic algorithm evolution.
        
        Args:
            images: Training images (BGR format)
            ground_truths: Ground truth segmentation masks
            verbose: Whether to print progress
            
        Returns:
            Best genome found
        """
        # Initialize population
        population = self.initialize_population(smart_init=True)
        
        # Evaluate initial population
        for genome in population:
            genome.fitness = self.evaluator.evaluate_genome(genome, images, ground_truths)
        
        # Track best fitness for early stopping
        best_fitness_ever = 0
        generations_without_improvement = 0
        
        for gen in range(self.num_generations):
            # Sort population by fitness
            population = sorted(population, key=lambda g: g.fitness, reverse=True)
            
            # Record statistics
            fitnesses = [g.fitness for g in population]
            stats = EvolutionStats(
                generation=gen,
                best_fitness=max(fitnesses),
                avg_fitness=np.mean(fitnesses),
                worst_fitness=min(fitnesses),
                best_genome=population[0].copy()
            )
            self.history.append(stats)
            
            if verbose:
                print(f"Gen {gen:3d}: Best={stats.best_fitness:.4f}, "
                      f"Avg={stats.avg_fitness:.4f}, Worst={stats.worst_fitness:.4f}")
            
            # Check early stopping
            if stats.best_fitness > best_fitness_ever:
                best_fitness_ever = stats.best_fitness
                generations_without_improvement = 0
                self.best_genome = population[0].copy()
            else:
                generations_without_improvement += 1
            
            if stats.best_fitness >= self.fitness_threshold:
                if verbose:
                    print(f"Fitness threshold {self.fitness_threshold} reached!")
                break
            
            if generations_without_improvement >= self.early_stopping:
                if verbose:
                    print(f"Early stopping: No improvement for {self.early_stopping} generations")
                break
            
            # Create next generation
            population = self.create_next_generation(population)
            
            # Evaluate new population
            for genome in population:
                genome.fitness = self.evaluator.evaluate_genome(genome, images, ground_truths)
        
        return self.best_genome
    
    def get_evolution_history(self) -> List[EvolutionStats]:
        """Get the evolution history."""
        return self.history


def run_optimization(images: List[np.ndarray],
                    ground_truths: List[np.ndarray],
                    config: dict = None,
                    verbose: bool = True) -> Tuple[Genome, List[EvolutionStats]]:
    """
    Run the complete genetic algorithm optimization.
    
    Args:
        images: Training images (BGR format)
        ground_truths: Ground truth masks
        config: GA configuration
        verbose: Print progress
        
    Returns:
        Best genome and evolution history
    """
    ga = GeneticAlgorithm(config)
    best_genome = ga.evolve(images, ground_truths, verbose)
    
    return best_genome, ga.get_evolution_history()

