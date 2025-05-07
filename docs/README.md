Stats Project Part I: Markov Chain Weight Generator
============================

This project creates a csv file that represents the probabilites of the next word of a sequence a *Markov Chain*.


<img src="https://media3.giphy.com/media/7x3PHPSMXSONHFuOK4/giphy.gif?cid=6c09b95295yultse256r48opo703yu1qs79k85dt4tamaxee&ep=v1_gifs_search&rid=giphy.gif&ct=g"/>

Rough plan 
------
First go through the text and identify unique words 
Create columns and rows of the matrix with each unique word

For a given word, go through the whole text and count the number of times each different word comes after it. Possibly in vector of a class with a name and count as members. Do the division (to find probabilities) and add these numbers to the matrix. Having the words in the rows/colums and vector in the same order (alphabetical) might make writing the numbers easier.

Do this for all words of the matrix.

Abstract
-------



