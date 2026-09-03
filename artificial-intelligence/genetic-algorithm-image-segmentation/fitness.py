"""
Fitness Function Module for Genetic Algorithm

Fitness Function Justification:
==============================
We use F1-Score (Dice coefficient) as our primary fitness metric for the following reasons:

1. **Balanced Metric**: F1-Score is the harmonic mean of precision and recall, providing
   a balanced measure that penalizes both false positives and false negatives.

2. **Imbalanced Classes**: In image segmentation, the object (pomegranate) typically
   occupies a small portion of the image. F1-Score handles this imbalance better than
   simple accuracy, which would give misleadingly high scores by just predicting background.

3. **Interpretability**: F1-Score ranges from 0 to 1, where 1 means perfect segmentation.
   This makes it intuitive to understand and compare different solutions.

4. **Customizable Trade-offs**: Using F-beta score allows us to adjust the balance between
   precision and recall based on application needs:
   - beta < 1: Emphasizes precision (fewer false positives)
   - beta = 1: Balanced (standard F1)
   - beta > 1: Emphasizes recall (fewer false negatives)
   
   For pomegranate detection, we may prefer slightly higher recall (beta > 1) to ensure
   we capture all pomegranate pixels, even at the cost of some background pixels.

5. **Alternative Metrics**:
   - IoU (Jaccard Index): Similar to F1 but more penalizing for errors. We offer this option.
   - Pixel Accuracy: Not suitable due to class imbalance.
   - Weighted loss: Custom combination of FP and FN penalties for specific applications.
"""

import numpy as np
from typing import List, Tuple, Dict, Callable
import cv2

from genome import Genome
from segmentation import SegmentationPipeline
from config import FITNESS_CONFIG


class FitnessEvaluator:
    """
    Evaluates the fitness of a genome based on segmentation performance.
    """
    
    def __init__(self, config: dict = None):
        """
        Initialize the fitness evaluator.
        
        Args:
            config: Configuration dictionary
        """
        self.config = config or FITNESS_CONFIG
        self.metric = self.config.get('metric', 'f1_score')
        self.beta = self.config.get('beta', 1.0)
        self.fp_weight = self.config.get('false_positive_weight', 1.0)
        self.fn_weight = self.config.get('false_negative_weight', 1.0)
    
    @staticmethod
    def compute_confusion_matrix(pred_mask: np.ndarray, 
                                  gt_mask: np.ndarray) -> Tuple[int, int, int, int]:
        """
        Compute confusion matrix values.
        
        Args:
            pred_mask: Predicted binary mask
            gt_mask: Ground truth binary mask
            
        Returns:
            (TP, TN, FP, FN) counts
        """
        # Ensure binary
        pred = (pred_mask > 0).astype(np.uint8)
        gt = (gt_mask > 0).astype(np.uint8)
        
        tp = np.sum((pred == 1) & (gt == 1))
        tn = np.sum((pred == 0) & (gt == 0))
        fp = np.sum((pred == 1) & (gt == 0))
        fn = np.sum((pred == 0) & (gt == 1))
        
        return tp, tn, fp, fn
    
    @staticmethod
    def compute_precision(tp: int, fp: int) -> float:
        """Compute precision metric."""
        if tp + fp == 0:
            return 0.0
        return tp / (tp + fp)
    
    @staticmethod
    def compute_recall(tp: int, fn: int) -> float:
        """Compute recall metric."""
        if tp + fn == 0:
            return 0.0
        return tp / (tp + fn)
    
    def compute_f_score(self, tp: int, fp: int, fn: int, beta: float = 1.0) -> float:
        """
        Compute F-beta score.
        
        F_beta = (1 + beta^2) * (precision * recall) / (beta^2 * precision + recall)
        
        Args:
            tp: True positives
            fp: False positives
            fn: False negatives
            beta: Beta parameter (1 for F1-score)
            
        Returns:
            F-beta score
        """
        precision = self.compute_precision(tp, fp)
        recall = self.compute_recall(tp, fn)
        
        if precision + recall == 0:
            return 0.0
        
        beta_sq = beta ** 2
        f_score = (1 + beta_sq) * (precision * recall) / (beta_sq * precision + recall)
        
        return f_score
    
    @staticmethod
    def compute_iou(tp: int, fp: int, fn: int) -> float:
        """
        Compute Intersection over Union (Jaccard Index).
        
        IoU = TP / (TP + FP + FN)
        
        Args:
            tp: True positives
            fp: False positives
            fn: False negatives
            
        Returns:
            IoU score
        """
        if tp + fp + fn == 0:
            return 1.0  # Both masks are empty
        return tp / (tp + fp + fn)
    
    @staticmethod
    def compute_dice(tp: int, fp: int, fn: int) -> float:
        """
        Compute Dice coefficient (same as F1-score).
        
        Dice = 2*TP / (2*TP + FP + FN)
        
        Args:
            tp: True positives
            fp: False positives
            fn: False negatives
            
        Returns:
            Dice coefficient
        """
        if 2 * tp + fp + fn == 0:
            return 1.0
        return (2 * tp) / (2 * tp + fp + fn)
    
    def compute_weighted_score(self, tp: int, tn: int, fp: int, fn: int) -> float:
        """
        Compute weighted score with custom FP and FN weights.
        
        Score = 1 - (fp_weight * FP + fn_weight * FN) / (total_pixels)
        
        Args:
            tp, tn, fp, fn: Confusion matrix values
            
        Returns:
            Weighted score (higher is better)
        """
        total = tp + tn + fp + fn
        if total == 0:
            return 0.0
        
        weighted_error = (self.fp_weight * fp + self.fn_weight * fn) / total
        return max(0.0, 1.0 - weighted_error)
    
    def evaluate_single(self, pred_mask: np.ndarray, 
                        gt_mask: np.ndarray) -> float:
        """
        Evaluate fitness for a single image.
        
        Args:
            pred_mask: Predicted segmentation mask
            gt_mask: Ground truth mask
            
        Returns:
            Fitness score
        """
        tp, tn, fp, fn = self.compute_confusion_matrix(pred_mask, gt_mask)
        
        if self.metric == 'f1_score' or self.metric == 'dice':
            return self.compute_f_score(tp, fp, fn, beta=1.0)
        elif self.metric == 'f_beta':
            return self.compute_f_score(tp, fp, fn, beta=self.beta)
        elif self.metric == 'iou':
            return self.compute_iou(tp, fp, fn)
        elif self.metric == 'weighted':
            return self.compute_weighted_score(tp, tn, fp, fn)
        else:
            return self.compute_f_score(tp, fp, fn, beta=1.0)
    
    def evaluate_genome(self, genome: Genome, 
                        images: List[np.ndarray],
                        ground_truths: List[np.ndarray]) -> float:
        """
        Evaluate fitness of a genome across multiple images.
        
        Args:
            genome: Genome to evaluate
            images: List of input BGR images
            ground_truths: List of ground truth masks
            
        Returns:
            Average fitness score
        """
        if len(images) == 0:
            return 0.0
        
        pipeline = SegmentationPipeline(genome)
        total_fitness = 0.0
        
        for image, gt in zip(images, ground_truths):
            pred_mask = pipeline.process(image)
            fitness = self.evaluate_single(pred_mask, gt)
            total_fitness += fitness
        
        return total_fitness / len(images)
    
    def get_detailed_metrics(self, pred_mask: np.ndarray, 
                             gt_mask: np.ndarray) -> Dict[str, float]:
        """
        Get all metrics for detailed analysis.
        
        Args:
            pred_mask: Predicted mask
            gt_mask: Ground truth mask
            
        Returns:
            Dictionary of all metrics
        """
        tp, tn, fp, fn = self.compute_confusion_matrix(pred_mask, gt_mask)
        
        total = tp + tn + fp + fn
        accuracy = (tp + tn) / total if total > 0 else 0
        
        return {
            'accuracy': accuracy,
            'precision': self.compute_precision(tp, fp),
            'recall': self.compute_recall(tp, fn),
            'f1_score': self.compute_f_score(tp, fp, fn, 1.0),
            'f_beta': self.compute_f_score(tp, fp, fn, self.beta),
            'iou': self.compute_iou(tp, fp, fn),
            'dice': self.compute_dice(tp, fp, fn),
            'tp': tp,
            'tn': tn,
            'fp': fp,
            'fn': fn,
        }


def evaluate_population(population: List[Genome],
                       images: List[np.ndarray],
                       ground_truths: List[np.ndarray],
                       config: dict = None) -> List[Genome]:
    """
    Evaluate fitness for entire population.
    
    Args:
        population: List of genomes
        images: Training images
        ground_truths: Ground truth masks
        config: Fitness configuration
        
    Returns:
        Population with updated fitness scores
    """
    evaluator = FitnessEvaluator(config)
    
    for genome in population:
        genome.fitness = evaluator.evaluate_genome(genome, images, ground_truths)
    
    return population

