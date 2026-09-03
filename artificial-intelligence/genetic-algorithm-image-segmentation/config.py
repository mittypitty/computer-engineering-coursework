"""
Configuration file for Pomegranate Segmentation System
Contains all hyperparameters and settings for the Genetic Algorithm and segmentation pipeline.
"""

# =============================================================================
# GENETIC ALGORITHM PARAMETERS
# =============================================================================

GA_CONFIG = {
    # Population settings
    'population_size': 100,           # Number of individuals in population
    'num_generations': 50,            # Maximum number of generations
    'elite_size': 5,                  # Number of best individuals to keep unchanged
    
    # Selection parameters
    'tournament_size': 5,             # Tournament selection size
    
    # Crossover parameters
    'crossover_rate': 0.8,            # Probability of crossover
    'crossover_type': 'blend',        # Options: 'single_point', 'two_point', 'uniform', 'blend'
    'blend_alpha': 0.5,               # Alpha parameter for blend crossover (BLX-alpha)
    
    # Mutation parameters
    'mutation_rate': 0.15,            # Probability of mutation per gene
    'mutation_sigma': 10,             # Standard deviation for Gaussian mutation
    
    # Convergence criteria
    'early_stopping_generations': 10, # Stop if no improvement for this many generations
    'fitness_threshold': 0.95,        # Stop if fitness exceeds this value
    
    # Random seed for reproducibility
    'random_seed': 42,
}

# =============================================================================
# HSV THRESHOLD BOUNDS
# =============================================================================
# HSV ranges in OpenCV: H [0-179], S [0-255], V [0-255]

HSV_BOUNDS = {
    'h_low': (0, 179),
    'h_high': (0, 179),
    's_low': (0, 255),
    's_high': (0, 255),
    'v_low': (0, 255),
    'v_high': (0, 255),
}

# For pomegranate (red color), we might need two HSV ranges
# because red wraps around in the hue channel
MULTI_MASK_CONFIG = {
    'use_multi_mask': True,           # Enable multiple HSV masks
    'num_masks': 2,                   # Number of HSV masks to use
    'combine_operation': 'or',        # How to combine masks: 'or', 'and'
}

# =============================================================================
# SEGMENTATION PIPELINE PARAMETERS
# =============================================================================

PIPELINE_CONFIG = {
    # Pre-processing
    'use_blur': True,
    'blur_kernel_size': 5,            # Must be odd number
    'blur_type': 'gaussian',          # Options: 'gaussian', 'median', 'bilateral'
    
    # Post-processing (morphological operations)
    'use_morphology': True,
    'morph_kernel_size': 5,
    'morph_operations': ['open', 'close'],  # Applied in order
    'morph_iterations': 2,
}

# =============================================================================
# FITNESS FUNCTION PARAMETERS
# =============================================================================

FITNESS_CONFIG = {
    # Metric to use for fitness
    'metric': 'f1_score',             # Options: 'iou', 'dice', 'f1_score', 'weighted'
    
    # For weighted metric: balance between precision and recall
    # Higher beta favors recall (finding all pomegranate pixels)
    'beta': 1.0,                      # F-beta score parameter
    
    # Penalty weights for different error types
    'false_positive_weight': 1.0,     # Penalty for background classified as pomegranate
    'false_negative_weight': 1.5,     # Penalty for pomegranate classified as background
    # Higher FN weight because missing pomegranate pixels is worse than including some background
}

# =============================================================================
# DATA CONFIGURATION
# =============================================================================

DATA_CONFIG = {
    'train_ratio': 0.7,               # Ratio of data for training
    'val_ratio': 0.3,                 # Ratio of data for validation
    'image_extensions': ['.jpg', '.jpeg', '.png', '.bmp'],
}

# =============================================================================
# OUTPUT CONFIGURATION
# =============================================================================

OUTPUT_CONFIG = {
    'save_best_params': True,
    'save_evolution_history': True,
    'save_visualizations': True,
    'output_dir': 'results',
}

