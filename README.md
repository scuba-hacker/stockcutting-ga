# stockcutting-ga

The code was written on Windows 95 in 1998, so to expedite upload to github, the original code for Visual Studio 5 has been uploaded together with the Windows binaries. Initial check shows an issue with missing C++ Runtime DLLs so currently the exe won't run under Windows 10. Scuba Hacker will fix this!

In 1998, the Scuba Hacker aka Mark B. Jones, decided to do his MSc Dissertation in the subject area of Evolutionary Computing (a branch of AI) under his supervisor, Dr David Corne - now Professor at Heriot-Watt University, Global Goals Engineer (as of 2023). Scuba Hacker was awarded a Distinction from the University of Reading, UK. so he thinks it's high time, in 2023, to make the project write-up and code open source.

This is a genetic algorithm engine that allows the user to explore how different GA heuristics influence the finding (or not) of good solutions to the NP-Hard problem of stock cutting with minimal wastage. Consider the use-case of the cutting of rectangular panes of glass from one very large single piece of glass, or any other material such as cloth or, much more appealing, even cake - you want to have as little wastage as possible, which is a classic optimisation problem.

The problem space is constrained to rectangular source material and rectangular cut-outs. There is no reason that the GA engine could not be modified to solve for more complicated shapes. Scuba Hacker thinks, a mere 25 years later having not looked back at the code, that only two parts of the engine needs customising, which is the stock placement algorithm (ie the method for determining orientation and location of each small pane of glass on the large piece of glass) and the fitness function. Of course, that's a bit of a stretch but at a first approximation he thinks this is the majority of the work.

The engine is an educational demonstrator that explores all the different ways that a GA can be steered using much of the canon of GA techniques that were available at the end of the 20th Century, including:

* Gene and Chromosome Encoding
* Layout Placement Algorithms
* Crossover Operators: Order-based, Segment order-based, position-based, segmented position- based, half-uniform, edge-recombination, n-point feature
* Mutation Operators: Single gene swap mutation, multiple gene swap mutation, inversion mutation, shunt mutation, standard mutation, cataclysmic mutation
* Selector operators: Rank Selection, Tournament Selection, Best Selection, Worst Selection, Work by Rank (inverted selection)
* Generational Models: Steady State, Stochastic, Special Mutator - Random, Stochistic Hill Climbing, Steepest Ascent Hill Climbing, Simulated Annealing
* Evolution Drivers
* Fitness Functions
* Layout Determining Algorithms

Scuba Hacker hopes that he can repurpose the GA engine to optimise the Travelling Salesman NP-Hard problem as part of his Mercator Origins - Sat Nav and Telemetry Console - for scuba divers and snorkellers. This would allow efficient routes to be computed considering the diver's preferences, the length of the dive and the sea/lake conditions - eg colder dives will be shorter and slower to complete than warmer dives.

The entire repo is published under the MIT licence, which has these features:

Permits:            Commercial Use, Distribution, Modification, Private Use
Conditions of Use:  License and copyright notice must be included with the licensed material
Limitations to Use: Limitation of Liability and no warranty provided
