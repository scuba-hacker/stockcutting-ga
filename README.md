# stockcutting-ga

The code was written on Windows 95 in 1998, so to expedite upload to github, the original code for Visual Studio 5 has been uploaded together with the Windows binaries. Initial checks shows an issue with missing C++ Runtime DLLs so currently the exe won't run under Windows 10. Scuba Hacker will fix this!

In 1998, the Scuba Hacker aka Mark B. Jones, decided to do his MSc Dissertation in the subject area of Evolutionary Computing (a branch of AI) under his Supervisor, Dr David Corne . Scuba Hacker was awarded a Distinction from the University of Reading, UK. so he thinks it's high time, in 2023, to make the project write-up and code open source.

This is a genetic algorithm engine that allows the user to explore how different GA heuristics influence the finding (or not) of good solutions to the NP-Hard problem of stock cutting with minimal wastage. Consider the use-case of the cutting of rectangular panes of glass from one very large single piece of glass, or any other material such as cloth or, much more appealing, even cake! 

The problem space is constrained to rectangular source material and rectangular cut-outs. There is no reason that the GA engine could not be modified to solve for more complicated shapes. Scuba Hacker thinks, a mere 25 years later having not looked back at the code, that only one part of the engine needs customising, which is the stock placement algorithm (ie the method for determining orientation and locatipn of each small pane of glass on the large piece of glass). Of course, that's a bit of a stretch but at a first approximation he thinks this is the majority of the work.

The engine is an educational demonstrator that explores all the different ways that a GA can be steered using the much of the canon of GA techniques that were available at the end of the 20th Century, including:

(list to be made complete...)

Generational Models
Stochastic Hill Climbing
Crossover and Mutation Operators
Cataclysmic Events

Scuba Hacker hopes that he can repurpose the GA engine to optimise the Travelling Salesman NP-Hard problem as part of his Mercator Origins - Sat Nav and Telemetry Console - for scuba divers and snorkellers. This would allow efficient routes to be computed considering the diver's preferences, the length of the dive and the sea/lake conditions - eg colder dives will be shorter and slower to complete than warmer dives.
