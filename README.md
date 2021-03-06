# Grassberger-Procaccia-Hough code for time series' model order estimation.

This package provides an object-oriented system, implemented in C++, to estimate the attractor dimension and the model order of a time series.

It is based on the Grassberger-Procaccia algorithm (Grassberger and Procaccia, 1983) which estimates the attractor dimension of a dynamic system as a correlation dimension. This algorithm requires to manually detect and compute the slope of the linear portion of the so-called log-log plot; in this package, this task is performed automatically with an ad-hoc implementation of the Hough transform for lines.

The `\code` directory contains the C++ source code for all the required classes. The Grassberger-Procaccia algorithm is implemented by the `LogLogPlotCalculator` class, while the Hough transform is implemented by the `HoughSlopeEstimator` class. See the attached class diagram for an overview of the class structure. A demo main is also provided as an example on how to use these classes to compute the model order for your time series.

The code is provided as is, with no guarantees except that bugs are almost surely present. This code's use is intended for research purpose only; for any other use, please, ask the author for permission. You can contact the author at the following address: camastra@ieee.org.

Published research reports using this code should cite the original article (accessible [here](https://doi.org/10.1016/j.envsoft.2022.105343)):

> F. Camastra, V. Capone, A. Ciaramella, A. Riccio, A. Staiano (2022). Prediction of Environmental Missing Data Time Series by Support Vector Machine Regression and Correlation Dimension Estimation. *Environmental Modelling and Software*.

#### This software package was developed by Vincenzo Capone, University of Naples 'Parthenope'.

<p align="center" width="100%">
    <img width="20%" src="https://user-images.githubusercontent.com/48727326/155006970-2c6bd1d5-330c-428b-b42f-f2cf14298f1e.png"> 
</p>
