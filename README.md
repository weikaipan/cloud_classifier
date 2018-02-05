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

1. Cloud objects have skewed distribution by their size since there are too many cloud fragments.
2. The K-Means Clustering Algorithm is biased by the huge amount the cloud fragments. 
3. The spatio resolution is too large so the satellite signal that represents a grid might not be a cloud in reality.

## Results

By dropping off most of fragment clouds and refining the research area to tropical regions where the large clouds have relative more amount than high latitude area, the result shows three main categories of cloud.
They are:

1. Clouds with large aspect ratio and height: maps to convective cloud and to East Indies where is famous for its strong convection.
2. Clouds with flat shape: maps to Cumulus clouds and to East Pacific (This is not representative enough so this part of analysis requires more data).
3. Clouds with fragment shape: This is where we can improve this project.



## Future Work

1. I plan to apply supervised learning algorithm on cloud labeled by K-Means clustering algorithm with physic variables retrieved from satellite image to identify the cloud type in different environment.
2. To generalize the project to global region.
3. To incorporate more domain knowledge in meteorology to identify all traditional cloud types.
4. To fix and require more data to build a more representative analysis.

## Credits

Advisor: Dr. Wei-Ting Chen, Department of Atmospheric Sciences, National Taiwan University, Taipei, Taiwan

Climatology of stratocumulus cloud morphologies: microphysical properties and radiative effects (A. Muhlbauer, I. L. McCoy, and R. Wood  ,23 May 2014 )

Objective identification of cloud regimes in the Tropical Western Pacific (Christian Jakob, George Tselioudis, 16 September 2003 )
