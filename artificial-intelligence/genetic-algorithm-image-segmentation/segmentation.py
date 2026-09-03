"""
HSV Color-based Segmentation Module
Applies the segmentation pipeline using HSV thresholds from the genome.
"""

import cv2
import numpy as np
from typing import Tuple, List, Optional

from genome import Genome, HSVThreshold
from config import PIPELINE_CONFIG, MULTI_MASK_CONFIG


class SegmentationPipeline:
    """
    Complete segmentation pipeline with:
    1. Pre-processing (optional blurring)
    2. HSV color-based segmentation
    3. Post-processing (optional morphological operations)
    """
    
    def __init__(self, genome: Genome, config: dict = None):
        """
        Initialize the segmentation pipeline.
        
        Args:
            genome: Genome containing HSV threshold parameters
            config: Optional configuration override
        """
        self.genome = genome
        self.config = config or PIPELINE_CONFIG
    
    def preprocess(self, image: np.ndarray) -> np.ndarray:
        """
        Apply pre-processing to the image.
        
        Args:
            image: Input BGR image
            
        Returns:
            Preprocessed image
        """
        if not self.config.get('use_blur', False):
            return image
        
        kernel_size = self.genome.blur_kernel
        # Ensure kernel size is odd
        if kernel_size % 2 == 0:
            kernel_size += 1
        
        blur_type = self.config.get('blur_type', 'gaussian')
        
        if blur_type == 'gaussian':
            return cv2.GaussianBlur(image, (kernel_size, kernel_size), 0)
        elif blur_type == 'median':
            return cv2.medianBlur(image, kernel_size)
        elif blur_type == 'bilateral':
            return cv2.bilateralFilter(image, kernel_size, 75, 75)
        else:
            return image
    
    def segment_with_threshold(self, hsv_image: np.ndarray, 
                                threshold: HSVThreshold) -> np.ndarray:
        """
        Apply a single HSV threshold to create a binary mask.
        
        Args:
            hsv_image: Image in HSV color space
            threshold: HSV threshold parameters
            
        Returns:
            Binary mask (0 or 255)
        """
        lower = threshold.get_lower_bound()
        upper = threshold.get_upper_bound()
        
        mask = cv2.inRange(hsv_image, lower, upper)
        return mask
    
    def segment(self, hsv_image: np.ndarray) -> np.ndarray:
        """
        Apply all HSV thresholds and combine masks.
        
        Args:
            hsv_image: Image in HSV color space
            
        Returns:
            Combined binary mask (0 or 255)
        """
        masks = []
        for threshold in self.genome.thresholds:
            mask = self.segment_with_threshold(hsv_image, threshold)
            masks.append(mask)
        
        if len(masks) == 1:
            return masks[0]
        
        # Combine masks based on configuration
        combine_op = MULTI_MASK_CONFIG.get('combine_operation', 'or')
        
        combined = masks[0]
        for mask in masks[1:]:
            if combine_op == 'or':
                combined = cv2.bitwise_or(combined, mask)
            elif combine_op == 'and':
                combined = cv2.bitwise_and(combined, mask)
        
        return combined
    
    def postprocess(self, mask: np.ndarray) -> np.ndarray:
        """
        Apply post-processing morphological operations.
        
        Args:
            mask: Binary mask (0 or 255)
            
        Returns:
            Processed mask
        """
        if not self.config.get('use_morphology', False):
            return mask
        
        kernel_size = self.genome.morph_kernel
        kernel = cv2.getStructuringElement(
            cv2.MORPH_ELLIPSE, (kernel_size, kernel_size)
        )
        
        operations = self.config.get('morph_operations', ['open', 'close'])
        iterations = self.config.get('morph_iterations', 2)
        
        result = mask
        for op in operations:
            if op == 'open':
                result = cv2.morphologyEx(result, cv2.MORPH_OPEN, kernel, iterations=iterations)
            elif op == 'close':
                result = cv2.morphologyEx(result, cv2.MORPH_CLOSE, kernel, iterations=iterations)
            elif op == 'dilate':
                result = cv2.dilate(result, kernel, iterations=iterations)
            elif op == 'erode':
                result = cv2.erode(result, kernel, iterations=iterations)
        
        return result
    
    def process(self, image: np.ndarray) -> np.ndarray:
        """
        Run the complete segmentation pipeline.
        
        Args:
            image: Input BGR image (as loaded by OpenCV)
            
        Returns:
            Binary segmentation mask (0 for background, 255 for foreground)
        """
        # Pre-processing
        preprocessed = self.preprocess(image)
        
        # Convert to HSV color space
        hsv_image = cv2.cvtColor(preprocessed, cv2.COLOR_BGR2HSV)
        
        # Segmentation
        mask = self.segment(hsv_image)
        
        # Post-processing
        final_mask = self.postprocess(mask)
        
        return final_mask
    
    def get_binary_mask(self, image: np.ndarray) -> np.ndarray:
        """
        Get binary mask with values 0 and 1 (instead of 0 and 255).
        
        Args:
            image: Input BGR image
            
        Returns:
            Binary mask (0 or 1)
        """
        mask = self.process(image)
        return (mask > 0).astype(np.uint8)


def apply_segmentation(image: np.ndarray, genome: Genome, 
                       config: dict = None) -> np.ndarray:
    """
    Convenience function to apply segmentation with a genome.
    
    Args:
        image: Input BGR image
        genome: Genome with HSV threshold parameters
        config: Optional pipeline configuration
        
    Returns:
        Binary mask (0 or 255)
    """
    pipeline = SegmentationPipeline(genome, config)
    return pipeline.process(image)


def visualize_segmentation(image: np.ndarray, mask: np.ndarray, 
                           alpha: float = 0.5) -> np.ndarray:
    """
    Create a visualization of the segmentation result.
    
    Args:
        image: Original BGR image
        mask: Binary mask (0 or 255)
        alpha: Blending factor for overlay
        
    Returns:
        Visualization image
    """
    # Create colored overlay
    overlay = np.zeros_like(image)
    overlay[mask > 0] = [0, 255, 0]  # Green for detected regions
    
    # Blend with original image
    result = cv2.addWeighted(image, 1 - alpha, overlay, alpha, 0)
    
    # Add contour outline
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    cv2.drawContours(result, contours, -1, (0, 0, 255), 2)
    
    return result

