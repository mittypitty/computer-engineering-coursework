"""
Simple Prediction Script for Pomegranate Segmentation
Usage:
    python predict.py image1.jpg image2.png ...
    python predict.py --input_dir ./test_images
"""

import argparse
import cv2
import numpy as np
import os
from pathlib import Path
import json
import matplotlib.pyplot as plt

from genome import Genome, HSVThreshold
from segmentation import SegmentationPipeline


def load_genome(path: str) -> Genome:
    """Load genome from JSON file."""
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


def predict_single(image_path: str, genome: Genome, output_dir: str, show: bool = True):
    """
    Predict segmentation for a single image.
    
    Args:
        image_path: Path to input image
        genome: Trained genome with HSV thresholds
        output_dir: Directory to save results
        show: Whether to display results
    """
    # Load image
    image = cv2.imread(image_path)
    if image is None:
        print(f"Error: Cannot load image {image_path}")
        return
    
    # Apply segmentation
    pipeline = SegmentationPipeline(genome)
    mask = pipeline.process(image)
    
    # Create output filename
    input_name = Path(image_path).stem
    mask_path = os.path.join(output_dir, f"{input_name}_mask.png")
    overlay_path = os.path.join(output_dir, f"{input_name}_overlay.png")
    
    # Save mask
    cv2.imwrite(mask_path, mask)
    print(f"Saved mask: {mask_path}")
    
    # Create overlay visualization
    overlay = image.copy()
    overlay[mask > 0] = [0, 255, 0]  # Green overlay
    blended = cv2.addWeighted(image, 0.6, overlay, 0.4, 0)
    
    # Draw contours
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(blended, contours, -1, (0, 0, 255), 2)
    
    cv2.imwrite(overlay_path, blended)
    print(f"Saved overlay: {overlay_path}")
    
    # Display if requested
    if show:
        fig, axes = plt.subplots(1, 3, figsize=(15, 5))
        
        axes[0].imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        axes[0].set_title('Original Image')
        axes[0].axis('off')
        
        axes[1].imshow(mask, cmap='gray')
        axes[1].set_title('Segmentation Mask')
        axes[1].axis('off')
        
        axes[2].imshow(cv2.cvtColor(blended, cv2.COLOR_BGR2RGB))
        axes[2].set_title('Overlay')
        axes[2].axis('off')
        
        plt.tight_layout()
        plt.savefig(os.path.join(output_dir, f"{input_name}_comparison.png"), dpi=150)
        plt.show()
    
    return mask


def main():
    parser = argparse.ArgumentParser(description='Predict pomegranate segmentation on new images')
    
    parser.add_argument('images', nargs='*', help='Image file paths')
    parser.add_argument('--input_dir', type=str, help='Directory containing images')
    parser.add_argument('--output_dir', type=str, default='./predictions', help='Output directory')
    parser.add_argument('--genome', type=str, default='./results/best_genome.json', help='Path to genome JSON')
    parser.add_argument('--no_show', action='store_true', help='Disable visualization')
    
    args = parser.parse_args()
    
    # Create output directory
    os.makedirs(args.output_dir, exist_ok=True)
    
    # Load genome
    if not os.path.exists(args.genome):
        print(f"Error: Genome file not found: {args.genome}")
        print("Please run training first or specify correct genome path with --genome")
        return
    
    print(f"Loading genome from {args.genome}...")
    genome = load_genome(args.genome)
    print(f"Loaded genome with fitness: {genome.fitness:.4f}")
    print(genome)
    
    # Collect image paths
    image_paths = []
    
    if args.images:
        image_paths.extend(args.images)
    
    if args.input_dir:
        extensions = ['.jpg', '.jpeg', '.png', '.bmp']
        for ext in extensions:
            image_paths.extend(Path(args.input_dir).glob(f'*{ext}'))
            image_paths.extend(Path(args.input_dir).glob(f'*{ext.upper()}'))
    
    if not image_paths:
        print("No images provided. Usage:")
        print("  python predict.py image1.jpg image2.png")
        print("  python predict.py --input_dir ./test_images")
        return
    
    print(f"\nProcessing {len(image_paths)} images...")
    
    for i, img_path in enumerate(image_paths):
        print(f"\n[{i+1}/{len(image_paths)}] Processing: {img_path}")
        predict_single(str(img_path), genome, args.output_dir, show=not args.no_show)
    
    print(f"\nDone! Results saved to {args.output_dir}")


if __name__ == '__main__':
    main()
