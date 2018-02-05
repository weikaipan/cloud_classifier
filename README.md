# Objective Tropical Cloud Classifier (Jan. 2016)

This independent project is to experiment a method to automate the cloud classfication process in meteorology.

## Data

1. [DARDAR](http://www.icare.univ-lille1.fr/projects/dardar) project which integrates CloudSat, CALIPSO, MODIS satellite images.
2. Spatio Resolution: (horizontal distance, vertical distnace) = (1100 meters * 60 meters)
3. Variable used: DARMASK_Simplified_Categorization

## Method

1. Connected-Component Algorithm
2. K-Means Clustering Algorithm

## Work Flow

1. Search cloud objects by using Connected-Component Algorithm
2. Define attributes of each cloud objects with (aspect ratio, size, vertical height)
3. Feature Scaling and Normalization
4. Classify by K-Means Clustering Algorithm

## Drawbacks

1. 

## Results

## History

TODO: Write history

## Credits

Advisor: Dr. Wei-Ting Chen

Climatology of stratocumulus cloud morphologies: microphysical properties and radiative effects (A. Muhlbauer, I. L. McCoy, and R. Wood  ,23 May 2014 )

Objective identification of cloud regimes in the Tropical Western Pacific (Christian Jakob, George Tselioudis, 16 September 2003 )

## License

TODO: Write license
