"""
Data Loading and Management Utilities

Handles:
- Loading images and ground truth masks
- Train/validation split
- Data augmentation (optional)
"""

import os
import cv2
import numpy as np
from typing import List, Tuple, Optional
from pathlib import Path
import random

from config import DATA_CONFIG


class DataLoader:
    """
    Handles loading and splitting of image data.
    
    Expected directory structure:
    data/
        images/
            image1.jpg
            image2.jpg
            ...
        masks/
            image1.png  (or image1_mask.png)
            image2.png
            ...
    """
    
    def __init__(self, data_dir: str, config: dict = None):
        """
        Initialize the data loader.
        
        Args:
            data_dir: Root directory containing 'images' and 'masks' folders
            config: Data configuration
        """
        self.data_dir = Path(data_dir)
        self.config = config or DATA_CONFIG
        
        self.images_dir = self.data_dir / 'images'
        self.masks_dir = self.data_dir / 'masks'
        
        self.extensions = self.config.get('image_extensions', ['.jpg', '.jpeg', '.png', '.bmp'])
        
        self.image_paths: List[Path] = []
        self.mask_paths: List[Path] = []
        
        self._load_file_list()
    
    def _load_file_list(self) -> None:
        """Load list of image and mask file paths."""
        if not self.images_dir.exists():
            print(f"Warning: Images directory not found: {self.images_dir}")
            return
        
        if not self.masks_dir.exists():
            print(f"Warning: Masks directory not found: {self.masks_dir}")
            return
        
        for img_path in self.images_dir.iterdir():
            if img_path.suffix.lower() not in self.extensions:
                continue
            
            # Try to find corresponding mask
            mask_path = self._find_mask(img_path)
            if mask_path is not None:
                self.image_paths.append(img_path)
                self.mask_paths.append(mask_path)
        
        print(f"Found {len(self.image_paths)} image-mask pairs")
    
    def _find_mask(self, image_path: Path) -> Optional[Path]:
        """
        Find the mask file corresponding to an image.
        
        Tries several naming conventions:
        - Same name with different extension
        - Name with _mask suffix
        - Name with _gt suffix
        - gt prefix (gt1.png for 1.png)
        - mask prefix
        
        Args:
            image_path: Path to the image file
            
        Returns:
            Path to mask file or None
        """
        stem = image_path.stem
        
        # Try different naming conventions
        possible_names = [
            stem,                       # Same name: 1.png -> 1.png
            f"{stem}_mask",             # Suffix: 1.png -> 1_mask.png
            f"{stem}_gt",               # Suffix: 1.png -> 1_gt.png
            f"{stem}_ground_truth",     # Suffix: 1.png -> 1_ground_truth.png
            f"gt{stem}",                # Prefix: 1.png -> gt1.png
            f"gt_{stem}",               # Prefix with underscore: 1.png -> gt_1.png
            f"mask{stem}",              # Prefix: 1.png -> mask1.png
            f"mask_{stem}",             # Prefix with underscore: 1.png -> mask_1.png
        ]
        
        for name in possible_names:
            for ext in self.extensions:
                mask_path = self.masks_dir / f"{name}{ext}"
                if mask_path.exists():
                    return mask_path
        
        return None
    
    def load_image(self, path: Path) -> np.ndarray:
        """
        Load an image from file.
        
        Args:
            path: Path to image file
            
        Returns:
            Image in BGR format
        """
        image = cv2.imread(str(path))
        if image is None:
            raise ValueError(f"Failed to load image: {path}")
        return image
    
    def load_mask(self, path: Path) -> np.ndarray:
        """
        Load a mask from file.
        
        Args:
            path: Path to mask file
            
        Returns:
            Binary mask (0 or 255)
        """
        mask = cv2.imread(str(path), cv2.IMREAD_GRAYSCALE)
        if mask is None:
            raise ValueError(f"Failed to load mask: {path}")
        
        # Ensure binary
        _, mask = cv2.threshold(mask, 127, 255, cv2.THRESH_BINARY)
        return mask
    
    def load_all(self) -> Tuple[List[np.ndarray], List[np.ndarray]]:
        """
        Load all images and masks.
        
        Returns:
            (images, masks) lists
        """
        images = []
        masks = []
        
        for img_path, mask_path in zip(self.image_paths, self.mask_paths):
            try:
                image = self.load_image(img_path)
                mask = self.load_mask(mask_path)
                images.append(image)
                masks.append(mask)
            except Exception as e:
                print(f"Error loading {img_path}: {e}")
        
        return images, masks
    
    def train_val_split(self, random_seed: int = 42) -> Tuple[
        Tuple[List[np.ndarray], List[np.ndarray]],
        Tuple[List[np.ndarray], List[np.ndarray]]
    ]:
        """
        Split data into training and validation sets.
        
        Args:
            random_seed: Random seed for reproducibility
            
        Returns:
            ((train_images, train_masks), (val_images, val_masks))
        """
        images, masks = self.load_all()
        
        if len(images) == 0:
            return ([], []), ([], [])
        
        # Shuffle indices
        indices = list(range(len(images)))
        random.seed(random_seed)
        random.shuffle(indices)
        
        # Split
        train_ratio = self.config.get('train_ratio', 0.7)
        split_idx = int(len(indices) * train_ratio)
        
        train_indices = indices[:split_idx]
        val_indices = indices[split_idx:]
        
        train_images = [images[i] for i in train_indices]
        train_masks = [masks[i] for i in train_indices]
        val_images = [images[i] for i in val_indices]
        val_masks = [masks[i] for i in val_indices]
        
        print(f"Train set: {len(train_images)} images")
        print(f"Validation set: {len(val_images)} images")
        
        return (train_images, train_masks), (val_images, val_masks)
    
    def get_file_paths(self) -> Tuple[List[Path], List[Path]]:
        """Get the loaded file paths."""
        return self.image_paths.copy(), self.mask_paths.copy()


def create_sample_data(output_dir: str, num_samples: int = 5) -> None:
    """
    Create sample data structure with placeholder images.
    This is useful for testing when no real data is available.
    
    Args:
        output_dir: Directory to create sample data in
        num_samples: Number of sample images to create
    """
    output_path = Path(output_dir)
    images_dir = output_path / 'images'
    masks_dir = output_path / 'masks'
    
    images_dir.mkdir(parents=True, exist_ok=True)
    masks_dir.mkdir(parents=True, exist_ok=True)
    
    for i in range(num_samples):
        # Create a simple image with a red circle (simulating pomegranate)
        img = np.zeros((480, 640, 3), dtype=np.uint8)
        img[:, :] = [200, 200, 200]  # Gray background
        
        # Random red circle
        center = (np.random.randint(100, 540), np.random.randint(100, 380))
        radius = np.random.randint(50, 100)
        
        # Red color in BGR
        red_color = (
            np.random.randint(0, 50),      # B
            np.random.randint(0, 50),      # G
            np.random.randint(150, 255)    # R
        )
        cv2.circle(img, center, radius, red_color, -1)
        
        # Add some noise
        noise = np.random.randint(-20, 20, img.shape, dtype=np.int16)
        img = np.clip(img.astype(np.int16) + noise, 0, 255).astype(np.uint8)
        
        # Create corresponding mask
        mask = np.zeros((480, 640), dtype=np.uint8)
        cv2.circle(mask, center, radius, 255, -1)
        
        # Save
        cv2.imwrite(str(images_dir / f'sample_{i:03d}.jpg'), img)
        cv2.imwrite(str(masks_dir / f'sample_{i:03d}.png'), mask)
    
    print(f"Created {num_samples} sample images in {output_dir}")


def load_single_image(path: str) -> np.ndarray:
    """
    Convenience function to load a single image.
    
    Args:
        path: Path to image file
        
    Returns:
        Image in BGR format
    """
    image = cv2.imread(path)
    if image is None:
        raise ValueError(f"Failed to load image: {path}")
    return image


def save_mask(mask: np.ndarray, path: str) -> None:
    """
    Save a binary mask to file.
    
    Args:
        mask: Binary mask (0 or 255, or 0 or 1)
        path: Output path
    """
    # Ensure proper format
    if mask.max() <= 1:
        mask = (mask * 255).astype(np.uint8)
    cv2.imwrite(path, mask)

