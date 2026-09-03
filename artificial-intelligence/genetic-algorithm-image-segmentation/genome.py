"""
Genome Design for Genetic Algorithm
Represents the HSV threshold parameters that define the segmentation.
"""

import numpy as np
from dataclasses import dataclass, field
from typing import List, Tuple, Optional
import copy

from config import HSV_BOUNDS, MULTI_MASK_CONFIG, PIPELINE_CONFIG


@dataclass
class HSVThreshold:
    """
    Represents a single HSV threshold range.
    Each threshold defines lower and upper bounds for H, S, V channels.
    """
    h_low: int
    h_high: int
    s_low: int
    s_high: int
    v_low: int
    v_high: int
    
    def to_array(self) -> np.ndarray:
        """Convert threshold to numpy array."""
        return np.array([
            self.h_low, self.h_high,
            self.s_low, self.s_high,
            self.v_low, self.v_high
        ], dtype=np.int32)
    
    @classmethod
    def from_array(cls, arr: np.ndarray) -> 'HSVThreshold':
        """Create threshold from numpy array."""
        return cls(
            h_low=int(arr[0]), h_high=int(arr[1]),
            s_low=int(arr[2]), s_high=int(arr[3]),
            v_low=int(arr[4]), v_high=int(arr[5])
        )
    
    def get_lower_bound(self) -> np.ndarray:
        """Get lower bound as numpy array for cv2.inRange."""
        return np.array([self.h_low, self.s_low, self.v_low], dtype=np.uint8)
    
    def get_upper_bound(self) -> np.ndarray:
        """Get upper bound as numpy array for cv2.inRange."""
        return np.array([self.h_high, self.s_high, self.v_high], dtype=np.uint8)
    
    def validate_and_fix(self) -> None:
        """Ensure low <= high for all channels and values are within bounds."""
        # Clamp to valid ranges
        self.h_low = np.clip(self.h_low, HSV_BOUNDS['h_low'][0], HSV_BOUNDS['h_low'][1])
        self.h_high = np.clip(self.h_high, HSV_BOUNDS['h_high'][0], HSV_BOUNDS['h_high'][1])
        self.s_low = np.clip(self.s_low, HSV_BOUNDS['s_low'][0], HSV_BOUNDS['s_low'][1])
        self.s_high = np.clip(self.s_high, HSV_BOUNDS['s_high'][0], HSV_BOUNDS['s_high'][1])
        self.v_low = np.clip(self.v_low, HSV_BOUNDS['v_low'][0], HSV_BOUNDS['v_low'][1])
        self.v_high = np.clip(self.v_high, HSV_BOUNDS['v_high'][0], HSV_BOUNDS['v_high'][1])
        
        # Ensure low <= high
        if self.h_low > self.h_high:
            self.h_low, self.h_high = self.h_high, self.h_low
        if self.s_low > self.s_high:
            self.s_low, self.s_high = self.s_high, self.s_low
        if self.v_low > self.v_high:
            self.v_low, self.v_high = self.v_high, self.v_low


@dataclass
class Genome:
    """
    Complete genome for the segmentation optimization.
    Contains one or more HSV thresholds and optional pipeline parameters.
    
    Genome Structure:
    - For single mask: 6 genes (h_low, h_high, s_low, s_high, v_low, v_high)
    - For multiple masks: 6 * num_masks genes
    - Optional: blur kernel size, morphology kernel size
    """
    thresholds: List[HSVThreshold] = field(default_factory=list)
    blur_kernel: int = 5
    morph_kernel: int = 5
    fitness: float = 0.0
    
    def __post_init__(self):
        if not self.thresholds:
            num_masks = MULTI_MASK_CONFIG['num_masks'] if MULTI_MASK_CONFIG['use_multi_mask'] else 1
            self.thresholds = [self._create_random_threshold() for _ in range(num_masks)]
    
    @staticmethod
    def _create_random_threshold() -> HSVThreshold:
        """Create a random HSV threshold."""
        # Initialize with values typical for red objects (pomegranate)
        # Red in HSV is around 0-10 and 170-179 (wraps around)
        return HSVThreshold(
            h_low=np.random.randint(0, 20),
            h_high=np.random.randint(5, 30),
            s_low=np.random.randint(50, 150),
            s_high=np.random.randint(150, 255),
            v_low=np.random.randint(30, 100),
            v_high=np.random.randint(150, 255)
        )
    
    @classmethod
    def create_random(cls, use_pipeline_genes: bool = False) -> 'Genome':
        """Create a completely random genome."""
        num_masks = MULTI_MASK_CONFIG['num_masks'] if MULTI_MASK_CONFIG['use_multi_mask'] else 1
        
        thresholds = []
        for i in range(num_masks):
            if num_masks == 2 and i == 1:
                # Second mask for red hue wrap-around (high hue values)
                threshold = HSVThreshold(
                    h_low=np.random.randint(160, 175),
                    h_high=np.random.randint(175, 179),
                    s_low=np.random.randint(50, 150),
                    s_high=np.random.randint(150, 255),
                    v_low=np.random.randint(30, 100),
                    v_high=np.random.randint(150, 255)
                )
            else:
                threshold = HSVThreshold(
                    h_low=np.random.randint(0, 179),
                    h_high=np.random.randint(0, 179),
                    s_low=np.random.randint(0, 255),
                    s_high=np.random.randint(0, 255),
                    v_low=np.random.randint(0, 255),
                    v_high=np.random.randint(0, 255)
                )
            threshold.validate_and_fix()
            thresholds.append(threshold)
        
        blur_kernel = np.random.choice([3, 5, 7, 9]) if use_pipeline_genes else 5
        morph_kernel = np.random.choice([3, 5, 7, 9]) if use_pipeline_genes else 5
        
        return cls(thresholds=thresholds, blur_kernel=blur_kernel, morph_kernel=morph_kernel)
    
    @classmethod
    def create_for_red_objects(cls) -> 'Genome':
        """Create a genome initialized for red object detection (pomegranate)."""
        if MULTI_MASK_CONFIG['use_multi_mask'] and MULTI_MASK_CONFIG['num_masks'] >= 2:
            # Two masks for red: one for low hue, one for high hue (wrap-around)
            thresholds = [
                HSVThreshold(
                    h_low=np.random.randint(0, 10),
                    h_high=np.random.randint(10, 25),
                    s_low=np.random.randint(80, 150),
                    s_high=np.random.randint(200, 255),
                    v_low=np.random.randint(50, 100),
                    v_high=np.random.randint(200, 255)
                ),
                HSVThreshold(
                    h_low=np.random.randint(160, 170),
                    h_high=np.random.randint(175, 179),
                    s_low=np.random.randint(80, 150),
                    s_high=np.random.randint(200, 255),
                    v_low=np.random.randint(50, 100),
                    v_high=np.random.randint(200, 255)
                )
            ]
        else:
            thresholds = [
                HSVThreshold(
                    h_low=np.random.randint(0, 10),
                    h_high=np.random.randint(10, 25),
                    s_low=np.random.randint(80, 150),
                    s_high=np.random.randint(200, 255),
                    v_low=np.random.randint(50, 100),
                    v_high=np.random.randint(200, 255)
                )
            ]
        
        return cls(thresholds=thresholds)
    
    def to_array(self) -> np.ndarray:
        """Convert entire genome to flat numpy array."""
        arrays = [t.to_array() for t in self.thresholds]
        return np.concatenate(arrays)
    
    @classmethod
    def from_array(cls, arr: np.ndarray, num_masks: int = None) -> 'Genome':
        """Create genome from flat numpy array."""
        if num_masks is None:
            num_masks = MULTI_MASK_CONFIG['num_masks'] if MULTI_MASK_CONFIG['use_multi_mask'] else 1
        
        thresholds = []
        for i in range(num_masks):
            start_idx = i * 6
            threshold = HSVThreshold.from_array(arr[start_idx:start_idx + 6])
            threshold.validate_and_fix()
            thresholds.append(threshold)
        
        return cls(thresholds=thresholds)
    
    def copy(self) -> 'Genome':
        """Create a deep copy of the genome."""
        return copy.deepcopy(self)
    
    def get_num_genes(self) -> int:
        """Get total number of genes in the genome."""
        return len(self.thresholds) * 6
    
    def __repr__(self) -> str:
        threshold_strs = []
        for i, t in enumerate(self.thresholds):
            threshold_strs.append(
                f"  Mask {i+1}: H[{t.h_low}-{t.h_high}] S[{t.s_low}-{t.s_high}] V[{t.v_low}-{t.v_high}]"
            )
        return f"Genome(fitness={self.fitness:.4f}):\n" + "\n".join(threshold_strs)

