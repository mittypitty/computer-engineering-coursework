"""
Main Entry Point for Pomegranate Segmentation System

This script orchestrates the complete pipeline:
1. Load training and validation data
2. Run genetic algorithm optimization
3. Evaluate on validation set
4. Generate visualizations and reports

Usage:
    python main.py --data_dir ./data --output_dir ./results

For testing without real data:
    python main.py --create_sample_data --data_dir ./sample_data
"""

import argparse
import os
import sys
import json
from pathlib import Path
from datetime import datetime

import cv2
import numpy as np

# Add parent directory to path for imports
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from config import GA_CONFIG, PIPELINE_CONFIG, FITNESS_CONFIG, OUTPUT_CONFIG, MULTI_MASK_CONFIG
from genome import Genome
from segmentation import SegmentationPipeline, apply_segmentation
from fitness import FitnessEvaluator
from genetic_algorithm import GeneticAlgorithm, run_optimization
from data_utils import DataLoader, create_sample_data, load_single_image, save_mask
from visualization import (
    plot_evolution_history,
    visualize_hsv_thresholds,
    evaluate_and_visualize,
    display_results_summary,
    create_final_report,
    create_comparison_image
)


def parse_args():
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(
        description='Pomegranate Segmentation using Genetic Algorithm'
    )
    
    parser.add_argument(
        '--data_dir', type=str, default='./data',
        help='Directory containing images/ and masks/ folders'
    )
    
    parser.add_argument(
        '--output_dir', type=str, default='./results',
        help='Directory to save results'
    )
    
    parser.add_argument(
        '--create_sample_data', action='store_true',
        help='Create sample data for testing'
    )
    
    parser.add_argument(
        '--num_samples', type=int, default=10,
        help='Number of sample images to create (if --create_sample_data)'
    )
    
    parser.add_argument(
        '--population_size', type=int, default=None,
        help='Override population size'
    )
    
    parser.add_argument(
        '--generations', type=int, default=None,
        help='Override number of generations'
    )
    
    parser.add_argument(
        '--no_visualize', action='store_true',
        help='Disable visualization'
    )
    
    parser.add_argument(
        '--predict', type=str, default=None,
        help='Path to image for prediction (use saved genome)'
    )
    
    parser.add_argument(
        '--genome_path', type=str, default=None,
        help='Path to saved genome JSON file'
    )
    
    return parser.parse_args()


def save_genome(genome: Genome, path: str) -> None:
    """
    Save genome parameters to JSON file.
    
    Args:
        genome: Genome to save
        path: Output path
    """
    data = {
        'thresholds': [
            {
                'h_low': int(t.h_low), 'h_high': int(t.h_high),
                's_low': int(t.s_low), 's_high': int(t.s_high),
                'v_low': int(t.v_low), 'v_high': int(t.v_high)
            }
            for t in genome.thresholds
        ],
        'blur_kernel': int(genome.blur_kernel),
        'morph_kernel': int(genome.morph_kernel),
        'fitness': float(genome.fitness)
    }
    
    with open(path, 'w') as f:
        json.dump(data, f, indent=2)
    
    print(f"Genome saved to {path}")


def load_genome(path: str) -> Genome:
    """
    Load genome from JSON file.
    
    Args:
        path: Path to JSON file
        
    Returns:
        Loaded genome
    """
    from genome import HSVThreshold
    
    with open(path, 'r') as f:
        data = json.load(f)
    
    thresholds = [
        HSVThreshold(
            h_low=t['h_low'], h_high=t['h_high'],
            s_low=t['s_low'], s_high=t['s_high'],
            v_low=t['v_low'], v_high=t['v_high']
        )
        for t in data['thresholds']
    ]
    
    genome = Genome(
        thresholds=thresholds,
        blur_kernel=data.get('blur_kernel', 5),
        morph_kernel=data.get('morph_kernel', 5),
        fitness=data.get('fitness', 0.0)
    )
    
    return genome


def run_training(args) -> Genome:
    """
    Run the complete training pipeline.
    
    Args:
        args: Command line arguments
        
    Returns:
        Best genome
    """
    print("\n" + "=" * 60)
    print("  POMEGRANATE SEGMENTATION - GENETIC ALGORITHM OPTIMIZATION")
    print("=" * 60)
    
    # Create output directory
    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Create sample data if requested
    if args.create_sample_data:
        print(f"\nCreating sample data in {args.data_dir}...")
        create_sample_data(args.data_dir, args.num_samples)
    
    # Load data
    print(f"\nLoading data from {args.data_dir}...")
    data_loader = DataLoader(args.data_dir)
    (train_images, train_masks), (val_images, val_masks) = data_loader.train_val_split()
    
    if len(train_images) == 0:
        print("ERROR: No training data found!")
        print(f"Please ensure {args.data_dir}/images/ and {args.data_dir}/masks/ exist")
        print("Or use --create_sample_data to generate test data")
        sys.exit(1)
    
    # Configure GA
    ga_config = GA_CONFIG.copy()
    if args.population_size:
        ga_config['population_size'] = args.population_size
    if args.generations:
        ga_config['num_generations'] = args.generations
    
    print(f"\n--- GA Configuration ---")
    print(f"Population size: {ga_config['population_size']}")
    print(f"Generations: {ga_config['num_generations']}")
    print(f"Crossover type: {ga_config['crossover_type']}")
    print(f"Mutation rate: {ga_config['mutation_rate']}")
    print(f"Multi-mask: {MULTI_MASK_CONFIG['use_multi_mask']}")
    
    # Run optimization
    print("\n--- Starting Evolution ---\n")
    best_genome, history = run_optimization(
        train_images, train_masks,
        config=ga_config,
        verbose=True
    )
    
    print("\n--- Best Genome Found ---")
    print(best_genome)
    
    # Save genome
    genome_path = output_dir / 'best_genome.json'
    save_genome(best_genome, str(genome_path))
    
    # Evaluate on training set
    print("\n--- Training Set Evaluation ---")
    train_metrics = evaluate_and_visualize(
        best_genome, train_images, train_masks,
        num_samples=3 if not args.no_visualize else 0,
        save_dir=str(output_dir / 'train_results') if not args.no_visualize else None
    )
    
    # Evaluate on validation set
    if len(val_images) > 0:
        print("\n--- Validation Set Evaluation ---")
        val_metrics = evaluate_and_visualize(
            best_genome, val_images, val_masks,
            num_samples=3 if not args.no_visualize else 0,
            save_dir=str(output_dir / 'val_results') if not args.no_visualize else None
        )
    else:
        val_metrics = {}
    
    # Visualizations
    if not args.no_visualize:
        # Evolution history plot
        plot_evolution_history(history, str(output_dir / 'evolution.png'))
        
        # HSV threshold visualization
        visualize_hsv_thresholds(best_genome)
    
    # Summary
    display_results_summary(train_metrics, val_metrics, best_genome)
    
    # Save report
    create_final_report(
        best_genome, train_metrics, val_metrics, history,
        str(output_dir / 'report.txt')
    )
    
    print(f"\nAll results saved to {output_dir}")
    
    return best_genome


def run_prediction(args) -> None:
    """
    Run prediction on a single image using saved genome.
    
    Args:
        args: Command line arguments
    """
    if not args.genome_path:
        genome_path = Path(args.output_dir) / 'best_genome.json'
        if not genome_path.exists():
            print("ERROR: No saved genome found. Run training first or specify --genome_path")
            sys.exit(1)
    else:
        genome_path = args.genome_path
    
    print(f"Loading genome from {genome_path}...")
    genome = load_genome(str(genome_path))
    print(genome)
    
    print(f"\nProcessing image: {args.predict}")
    image = load_single_image(args.predict)
    
    pipeline = SegmentationPipeline(genome)
    mask = pipeline.process(image)
    
    # Save mask
    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    
    input_name = Path(args.predict).stem
    mask_path = output_dir / f'{input_name}_mask.png'
    save_mask(mask, str(mask_path))
    print(f"Mask saved to {mask_path}")
    
    # Visualization
    if not args.no_visualize:
        import matplotlib.pyplot as plt
        
        comparison = create_comparison_image(image, mask)
        plt.figure(figsize=(12, 6))
        plt.imshow(comparison)
        plt.title('Segmentation Result')
        plt.axis('off')
        plt.savefig(str(output_dir / f'{input_name}_result.png'), dpi=150, bbox_inches='tight')
        plt.show()


def main():
    """Main entry point."""
    args = parse_args()
    
    if args.predict:
        run_prediction(args)
    else:
        run_training(args)


if __name__ == '__main__':
    main()

