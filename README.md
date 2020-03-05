# AB-KR-LF-MW-Project4

For this project, each teammate wrote their own unique algorithm for shuffling the vector of bank account objects. To determine which methods were most effective,
the team decided to implement a metric to calculate the "randomness" of each algorithm using the object's starting index and the index that it ended up at after the shuffle.
Calculating the distance that each object moved allows for calculations of the standard error to be computed as well. The greater the standard error, the better the shuffle
shuffled. There were 100 trials tested for different vector lengths (10, 25, 50), and the mean of the standard errors for all of these trials were computed and printed out
to the terminal. In addition to each of the teammate's methods, the shuffle method included with C++ is tested, as well as the "randomness" of the vector if it were reversed
(which isn't random, actually) to provide more context for algorithm comparison.

All algorithms sufficiently shuffle the vector (except for the non-random baseline, which doesn't actually shuffle, but just reverses the vectors order, providing no change
in the index distance travelled for each trial). All teammates were able to code an algorithm which provided a better shuffle than the included shuffle method in C++.




Due on Gradescope by Friday, March 6th

For this project, you will design and implement a C++ program that creates and evaluates
randomization algorithms.

## Requirements
- [x] You must work in a team of 2-4 people of your choosing for this project.

- [x] You cannot reuse code from previous projects.

- [x] All of your programming files should be in a private GitHub repository in your section’s organization.
   
    - [x] Your project name must include all team member’s initials and Project 4 (e.g. AB-CD-EFProject4).
  
    - [x] Have one team member create the repository and add the other members as collaborators
          (on GitHub, go to Settings —> Manage Access and add the others’ GitHub usernames).

- [x] Your repository should have a .gitignore file, a README file, and a CMakeLists.txt.

- [x] Create a class in header and .cpp files that includes at least two fields and at least one
      nontrivial method. It must also overload the << operator.

- [x] In another header file, write a template class that holds a vector of items and has methods to
      randomize, sort, and find items. It should also overload the << operator to print the vector of
      items. You can add other functionality as needed.
    
    - [ ] Each team member should write their own randomize method. They must all be included in
      the class. The method names should include the author’s initials.
   
    - [x] Write all of the code for this class in the header file. Do not create a corresponding .cpp file.

- [x] Your main program should have an object of the template class that holds objects of the other class.

- [ ] The goal of your program is to determine which of the randomize algorithms works best. This means you 
      need to agree as a team on some quantitative metric to determine the effectiveness of a randomizing 
      algorithm, test each randomize method according to your metric, and report in your README about 
      your results.

- [ ] The impressiveness of your program will be determined by the amount of creativity in your randomize 
      algorithms, the validity of your metric, and the thoroughness of your testing and explanation.

- [ ] All of the above must be pushed to your GitHub repository.

- [ ] On Gradescope, one teammate must submit the URL of the last commit and add the other teammates to 
      the submission.
     
## Grading
The project is out of 100 points.

- [ ] 5 pts Project compiles and runs. GitHub repository includes all files as described above.
- [ ] 10 pts (Individual pts) Push fair share of code to the repo throughout project lifetime.
- [ ] 10 pts Good, consistent coding style throughout project.
- [ ] 10 pts Declare and define one class in header and .cpp files as described above.
- [ ] 10 pts Declare and define one template class in a header file as described above.
- [ ] 10 pts (Individual pts) Write a custom randomization algorithm that is effective according to the metric.
- [ ] 10 pts Main program is fully functional.
- [ ] 20 pts The concept and execution of the metric are impressive.
- [ ] 15 pts The README file contains a professional report of the results as described above.

## Extra Credit
You can earn up to 10 pts extra credit for not using the built-in (pseudo-)random number generators in your 
randomization algorithm. Your algorithm should still be effective.
