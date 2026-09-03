"""
Visualization Utilities

Provides functions for:
- Displaying segmentation results
- Comparing predictions with ground truth
- Plotting evolution history
- Creating result summaries
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt
from typing import List, Tuple, Optional, Dict
from pathlib import Path

from genome import Genome
from segmentation import SegmentationPipeline
from fitness import FitnessEvaluator
from genetic_algorithm import EvolutionStats


def create_comparison_image(image: np.ndarray, 
                            pred_mask: np.ndarray,
                            gt_mask: np.ndarray = None,
                            alpha: float = 0.4) -> np.ndarray:
    """
    Create a side-by-side comparison visualization.
    
    Args:
        image: Original BGR image
        pred_mask: Predicted segmentation mask
        gt_mask: Ground truth mask (optional)
        alpha: Overlay transparency
        
    Returns:
        Comparison image
    """
    # Convert to RGB for display
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    
    # Create prediction overlay (green)
    pred_overlay = image_rgb.copy()
    pred_overlay[pred_mask > 0] = [0, 255, 0]
    pred_result = cv2.addWeighted(image_rgb, 1 - alpha, pred_overlay, alpha, 0)
    
    if gt_mask is not None:
        # Create ground truth overlay (blue)
        gt_overlay = image_rgb.copy()
        gt_overlay[gt_mask > 0] = [0, 0, 255]
        gt_result = cv2.addWeighted(image_rgb, 1 - alpha, gt_overlay, alpha, 0)
        
        # Create difference visualization
        # Green: True Positive, Red: False Positive, Blue: False Negative
        diff = np.zeros_like(image_rgb)
        pred_binary = pred_mask > 0
        gt_binary = gt_mask > 0
        
        tp_mask = pred_binary & gt_binary
        fp_mask = pred_binary & ~gt_binary
        fn_mask = ~pred_binary & gt_binary
        
        diff[tp_mask] = [0, 255, 0]   # Green - correct
        diff[fp_mask] = [255, 0, 0]   # Red - false positive
        diff[fn_mask] = [0, 0, 255]   # Blue - false negative
        
        # Combine all views
        h, w = image_rgb.shape[:2]
        result = np.zeros((h * 2, w * 2, 3), dtype=np.uint8)
        result[:h, :w] = image_rgb
        result[:h, w:] = pred_result
        result[h:, :w] = gt_result
        result[h:, w:] = diff
        
        # Add labels
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(result, "Original", (10, 30), font, 1, (255, 255, 255), 2)
        cv2.putText(result, "Prediction", (w + 10, 30), font, 1, (0, 255, 0), 2)
        cv2.putText(result, "Ground Truth", (10, h + 30), font, 1, (0, 0, 255), 2)
        cv2.putText(result, "Difference", (w + 10, h + 30), font, 1, (255, 255, 255), 2)
        
        return result
    else:
        # Without ground truth, just show original and prediction
        h, w = image_rgb.shape[:2]
        result = np.zeros((h, w * 2, 3), dtype=np.uint8)
        result[:, :w] = image_rgb
        result[:, w:] = pred_result
        
        return result


def plot_evolution_history(history: List[EvolutionStats], 
                           save_path: str = None) -> None:
    """
    Plot the evolution history showing fitness progression.
    
    Args:
        history: List of evolution statistics
        save_path: Path to save the plot (optional)
    """
    generations = [s.generation for s in history]
    best = [s.best_fitness for s in history]
    avg = [s.avg_fitness for s in history]
    worst = [s.worst_fitness for s in history]
    
    plt.figure(figsize=(12, 6))
    
    plt.subplot(1, 2, 1)
    plt.plot(generations, best, 'g-', label='Best', linewidth=2)
    plt.plot(generations, avg, 'b-', label='Average', linewidth=2)
    plt.plot(generations, worst, 'r-', label='Worst', linewidth=2)
    plt.xlabel('Generation')
    plt.ylabel('Fitness')
    plt.title('Fitness Evolution')
    plt.legend()
    plt.grid(True, alpha=0.3)
    
    plt.subplot(1, 2, 2)
    improvement = [best[i] - best[i-1] if i > 0 else 0 for i in range(len(best))]
    plt.bar(generations, improvement, color='green', alpha=0.7)
    plt.xlabel('Generation')
    plt.ylabel('Fitness Improvement')
    plt.title('Per-Generation Improvement')
    plt.grid(True, alpha=0.3)
    
    plt.tight_layout()
    
    if save_path:
        plt.savefig(save_path, dpi=150, bbox_inches='tight')
        print(f"Saved evolution plot to {save_path}")
    
    plt.show()


def visualize_hsv_thresholds(genome: Genome) -> None:
    """
    Visualize the HSV threshold ranges.
    
    Args:
        genome: Genome with threshold parameters
    """
    fig, axes = plt.subplots(len(genome.thresholds), 3, figsize=(15, 4 * len(genome.thresholds)))
    
    if len(genome.thresholds) == 1:
        axes = [axes]
    
    for i, threshold in enumerate(genome.thresholds):
        # Hue
        axes[i][0].barh(['Hue'], [threshold.h_high - threshold.h_low], 
                        left=[threshold.h_low], color='red', alpha=0.7)
        axes[i][0].set_xlim(0, 179)
        axes[i][0].set_title(f'Mask {i+1}: Hue Range [{threshold.h_low}-{threshold.h_high}]')
        
        # Saturation
        axes[i][1].barh(['Saturation'], [threshold.s_high - threshold.s_low],
                        left=[threshold.s_low], color='green', alpha=0.7)
        axes[i][1].set_xlim(0, 255)
        axes[i][1].set_title(f'Saturation Range [{threshold.s_low}-{threshold.s_high}]')
        
        # Value
        axes[i][2].barh(['Value'], [threshold.v_high - threshold.v_low],
                        left=[threshold.v_low], color='blue', alpha=0.7)
        axes[i][2].set_xlim(0, 255)
        axes[i][2].set_title(f'Value Range [{threshold.v_low}-{threshold.v_high}]')
    
    plt.tight_layout()
    plt.show()


def evaluate_and_visualize(genome: Genome,
                           images: List[np.ndarray],
                           ground_truths: List[np.ndarray],
                           num_samples: int = 5,
                           save_dir: str = None) -> Dict[str, float]:
    """
    Evaluate genome on multiple images and visualize results.
    
    Args:
        genome: Genome to evaluate
        images: List of images
        ground_truths: List of ground truth masks
        num_samples: Number of samples to visualize
        save_dir: Directory to save visualizations
        
    Returns:
        Dictionary of average metrics
    """
    pipeline = SegmentationPipeline(genome)
    evaluator = FitnessEvaluator()
    
    all_metrics = []
    
    if save_dir:
        Path(save_dir).mkdir(parents=True, exist_ok=True)
    
    num_to_show = min(num_samples, len(images))
    
    for i, (image, gt) in enumerate(zip(images, ground_truths)):
        pred_mask = pipeline.process(image)
        metrics = evaluator.get_detailed_metrics(pred_mask, gt)
        all_metrics.append(metrics)
        
        if i < num_to_show:
            # Create comparison visualization
            comparison = create_comparison_image(image, pred_mask, gt)
            
            if save_dir:
                save_path = Path(save_dir) / f'result_{i:03d}.png'
                # Convert RGB back to BGR for saving
                cv2.imwrite(str(save_path), cv2.cvtColor(comparison, cv2.COLOR_RGB2BGR))
            
            # Display
            plt.figure(figsize=(16, 8))
            plt.imshow(comparison)
            plt.title(f"Sample {i+1} - F1: {metrics['f1_score']:.4f}, IoU: {metrics['iou']:.4f}")
            plt.axis('off')
            plt.show()
    
    # Compute average metrics
    avg_metrics = {}
    for key in all_metrics[0].keys():
        if isinstance(all_metrics[0][key], (int, float)):
            avg_metrics[f'avg_{key}'] = np.mean([m[key] for m in all_metrics])
    
    print("\n=== Average Metrics ===")
    for key, value in avg_metrics.items():
        print(f"{key}: {value:.4f}")
    
    return avg_metrics


def display_results_summary(train_metrics: Dict[str, float],
                            val_metrics: Dict[str, float],
                            genome: Genome) -> None:
    """
    Display a summary of training and validation results.
    
    Args:
        train_metrics: Training set metrics
        val_metrics: Validation set metrics
        genome: Best genome
    """
    print("\n" + "=" * 60)
    print("                    RESULTS SUMMARY")
    print("=" * 60)
    
    print("\n--- Best Genome Parameters ---")
    print(genome)
    
    print("\n--- Training Set Performance ---")
    for key, value in train_metrics.items():
        if 'avg' in key:
            print(f"  {key}: {value:.4f}")
    
    print("\n--- Validation Set Performance ---")
    for key, value in val_metrics.items():
        if 'avg' in key:
            print(f"  {key}: {value:.4f}")
    
    # Calculate generalization gap
    if 'avg_f1_score' in train_metrics and 'avg_f1_score' in val_metrics:
        gap = train_metrics['avg_f1_score'] - val_metrics['avg_f1_score']
        print(f"\n--- Generalization ---")
        print(f"  F1 Score Gap (Train - Val): {gap:.4f}")
        if gap < 0.05:
            print("  Good generalization!")
        elif gap < 0.1:
            print("  Moderate generalization")
        else:
            print("  Warning: Possible overfitting")
    
    print("\n" + "=" * 60)


def create_final_report(genome: Genome,
                        train_metrics: Dict,
                        val_metrics: Dict,
                        history: List[EvolutionStats],
                        save_path: str) -> None:
    """
    Create a comprehensive final report.
    
    Args:
        genome: Best genome
        train_metrics: Training metrics
        val_metrics: Validation metrics
        history: Evolution history
        save_path: Path to save report
    """
    with open(save_path, 'w') as f:
        f.write("=" * 60 + "\n")
        f.write("POMEGRANATE SEGMENTATION - OPTIMIZATION REPORT\n")
        f.write("=" * 60 + "\n\n")
        
        f.write("--- Best Genome Parameters ---\n")
        f.write(str(genome) + "\n\n")
        
        f.write("--- Training Set Metrics ---\n")
        for key, value in train_metrics.items():
            f.write(f"{key}: {value:.4f}\n")
        
        f.write("\n--- Validation Set Metrics ---\n")
        for key, value in val_metrics.items():
            f.write(f"{key}: {value:.4f}\n")
        
        f.write("\n--- Evolution Summary ---\n")
        f.write(f"Total generations: {len(history)}\n")
        f.write(f"Initial best fitness: {history[0].best_fitness:.4f}\n")
        f.write(f"Final best fitness: {history[-1].best_fitness:.4f}\n")
        f.write(f"Improvement: {history[-1].best_fitness - history[0].best_fitness:.4f}\n")
    
    print(f"Report saved to {save_path}")

