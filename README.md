<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
# Parallel Jacobi

A comparison between different parallel implementations of the Jacobi algorithm for determining the solutions of a system of linear equations.

## Table of contents[![](./docs/img/pin.svg)](#table-of-contents)
1. [Implementation](#implementation)
2. [Structure](#structure)
3. [Compiling](#compiling)
4. [Running](#running)
5. [Results](#results)

## Implementation

The parallel versions of this algorithm that have been implemented are:

1. The matrix is divided by chunks of continuous rows, each chunk is assigned to a worker.
2. Parallel implementation using FastFlow library.

A sequential version of the program has also been implemented to perform comparisons.

## Structure

```
📦JacobiSPM
 ┣ 📂plot
 ┃ ┣ ...
 ┣ 📂src
 ┃ ┣ 📜CMakeLists.txt
 ┃ ┣ 📜Makefile
 ┃ ┣ 📜bash.sh
 ┃ ┣ 📜jacobi_ff.cpp
 ┃ ┣ 📜jacobi_ff.h
 ┃ ┣ 📜jacobi_sequential.cpp
 ┃ ┣ 📜jacobi_sequential.h
 ┃ ┣ 📜jacobi_threads.cpp
 ┃ ┣ 📜jacobi_threads.h
 ┃ ┣ 📜main.cpp
 ┃ ┣ 📜normcomputation.cpp
 ┃ ┣ 📜overhead.cpp
 ┃ ┣ 📜utility.cpp
 ┃ ┣ 📜utility.h
 ┃ ┣ 📜utimer.cpp
 ┃ ┣ 📜vectorization.cpp
 ┣ 📜Dockerfile.file
 ┣ 📜README.md                     
```

## Compiling

A Makefile was created to compile the various versions. To create the executable files, it is possible to execute the rule

```bash
    make
```

## Running

To run an experiment, it is possible to launch the program and pass the necessary arguments. An example is the following

```bash
    ./main.out [mode] [matrix_size] [number_iterations] [tolerance] [output_filename] [num_threads]
``` 

where
- **[mode]**: is the modality to execute the algorithm 
- - **[seq]**: sequential version
- - **[thr]**: native threads version
- - **[ff]**: FastFlow version
- **[matrix_size]**: is the length of the matrix and vector. A matrix of size matrix_size*matrix_size and a vector of length matrix_size will be created.
- **[number_iterations]**: Number of iterations to be performed for Jacobi's method.
- **[tolerance]**: is the stopping criteria in order to avoid to reach the maximum number of iterations.
- **[output_filename]: is the filename where the outputs will be saved (it is a csv file)
- **[num_threads]**: Degree of parallelism to be used.

To run all experiments at once run the file execute.sh

```bash
    ./bash.sh
``` 

## Results

Below are some results for completion time and speedup with matrixes of size $15.000 \times 15.000$

<p align="center">
<img src="plot/completiontime_15000size.png" height="250" />
<img src="plot/speedup_100iter_15000size_false.png" height="250" />
</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors](https://github.com/robbespo00/jacobi-spm/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/robbespo00/jacobi-spm/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/robbespo00/jacobi-spm/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/roberto-esposito-964a46176/
