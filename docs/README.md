Modern Text Prediction with Century Old Techniques
============================
[Text Generator](https://github.com/bepissbepisss/Markov-Chain-Text-Generator) | 
[Weight Generator](https://github.com/bepissbepisss/Markov-Chain-Weight-Generator)

Introduction
------

As the title suggests the goal of this experiment was to recreate text predictions similar to what one might see when typing on an iphone by implementing Markov Chains. The Markov Chains were implemented using the c++ programming language with the short story The Metamorphosis by Franz Kafka as a corpus. The decision to use second order Markov Chains to reduce the computational power needed to run the experiment limits it to a purely academic exercise. In this document the theory of Markov Chains and their assumptions will be discussed, then the data methodology used when conducting the experiment will be examined, later the results and expected results will be discussed and compared to modern text prediction algorithms specifically Bengio’s algorithm and finally a conclusion on the significance of the experiment will be produced.




Theory
-----

The Markov Chain discovered by Andrey Markov in the early 20th century is an essential analytical device for statistical observations. Markov uncovered the Markov chain whilst settling a disagreement about the assumptions needed in a different statistical test. 

A Markov Chain is a grouping of states with different transitions between each state where the transitions occur depending on their associated probabilities.
An example;
Imagine Dany is deciding which candy he wants to eat from his backpack. In his bag Dany has Jolly Ranchers (J), Candy Corn (C) and a Sour Keys(S). After quizzing Dany we find out that after having a Jolly Rancher there is a 20% Dany has another Jolly Rancher, a 70% he has a Candy Corn and a 10% he has a sour key. After more quizzing we are able to make a chart.

![image](https://github.com/user-attachments/assets/fe387164-b452-4aff-b038-cd7a31aa16f5)

 From this chart it is clear to see what the chances are that Dany chooses any given candy depending on what candy he has just had, this brings us to our fist important quality of the Markov Chain.

For the Markov Chain to function there is a key assumption and that is that the Markov Chain is a memoryless function. Similar to the Geometric and Exponential distributions, the memoryless property of the Markov Chain implies that the probability of any given future state depends solely on the present state and not the states before it. 
If we look back to Dany and his candy this property can be demonstrated as follows:
3 days ago Dany had a Candy Corn, 2 days ago Dany had a sour key, 1 day ago Dany had a sour key, today Dany had a Jolly Rancher, what is the most likely candy for tomorrow? Now knowing the memoryless property it is easy to see that Dany’s candy choice tomorrow is solely dependent on the probabilities leaving the J IE: Dany is most likely to have a Candy Corn with a 70% chance of it occurring. 

This example paired with an understanding of basic probabilities allow the following formula to be formulated.


“The Markov Property
For any positive integer n and possible states i0,i1,...,in of the random variables,
P(Xn=in|Xn-1=in-1)=P(Xn=in|X0=i0, X1=i1,...,Xn-1=in-1).”
(https://brilliant.org/wiki/markov-chains/) 

This reconfirms what was previously stated in saying that the next state Xn only depends on the previous state Xn-1 and not every preceding state. The memoryless property is incredibly significant for simplifying calculations and when gathering data. Needing only to get the information of the current state is much more efficient than gathering data of all previous states.

The other significant property of the Markov Chain is the ability to form a transition matrix. A transition matrix is a matrix composed of probabilities of changing from one state to another. Using the matrix allows for computational speeds to be increased. To form the matrix simply take the outgoing probabilities for each state and fill them into individual rows.



.2
.1
.7
.4
.6
.0
.15
.8
.05


J
S
C
P(J->J)
P(J->S)
P(J->C)
P(S->J)
P(S->S)
P(S->C)
P(C->J)
P(C->S)
P(C->C)


Using the properties of matrices and transitions matrices we can find what is called the two step matrix or P2. This matrix simply represents the probabilities of where we would end up after two choices. To find this matrix simply multiply the first matrix by itself.

P x P= 


J
S
C
J
.185
.175
.640
S
.3575
.1075
.535
C
.320
.280
.400









This table says that if Dany had a Jolly Rancher yesterday and now he's going to have two candies today the odds of the 2nd candy being a J is .185 of being an S is .175 and so on. Using this property if the steps are increased to infinity you can find the probability of being in any state.

EXPLAIN SECOND ORDER M CHAINS
Data methodology 
The project consists of two programs. The first program fills the entries of the matrix with probabilities from a data set following this pseudocode.

Iterate for every initial word in the sample
   Look at the next word that appears
   Count the number of times each next word appears
   Divide the number of times each next word appears by the total number of occurrences of the original word
   Write this data to the row of the matrix for the appropriate initial word

The second program… DANY

Discussion 
----
The results from these Markov chain text predictors were subpar compared to the modern industry standard of word generation. 
There are a few possible reasons for this failure in the program. The Markov chains used are only second order and thus only account for the past 2 words to predict the third word that comes along. This method may work in other scenarios but with an understanding of the complexity of language it is clear that this result is expected. To increase the success of this code it’s imperative to increase the order of the Markov chain.

An example of what was done in this experiment can be found from the following.

Imagine a text was weighed for its probability gives a result that red is most likely to come after colour. In a scenario where the previous two words are favourite colour it is not improbable that the sentence will make some sense by outputting something like: 
“Bob’s favourite colour red”.
However in a longer more complicated situation the generator will fail.
“Bob says he loves blue like the ocean, that's why Bob’s favourite colour red.”
Not only does it sound like a caveman but the generator is lacking context to make an appropriate prediction of the next word. 

This example clearly illustrates why increasing the order of the Markov chain proves so significant. The more the order is increased the more context the text generator has available and thus it can make a more accurate prediction. So this begs the question, when does the order become substantial to generate text. 

A study in the 90s by Stanley F.Chen and Joshua Goodman found that after 5 N-grams there was a big plateau in improvement to the perplexity (cross-entropy) of the text. This becomes a problem, the plateau that is reached at 5 N-grams can provide good text on a short sentence scale but will still frequently provide text that is incoherent and caveman-ish in longer discourses. If there was unlimited information time and money the obvious answer is to keep pushing the N-grams despite the aggressive plateau but in the real world this is impractical. It is exponentially more computationally expensive each time the N-gram is increased due to needing to count all the N-1 chains of words. The other reason it is practically impossible is because even with the internet’s incredible size there is a point at which there is not enough data for certain n-grams, take the 50th n-gram for example, to make a successful generator there needs to be reliable counts for every 49-word context, this is not likely to be found even on big internet corpuses. 

A comparison
----

Then language generation fails to ever reach a perfect coherence?
No, in the modern world every available text box has an autofill feature, countless websites use ai tools and chat GPT can generate professional level essays on any topic in a matter of seconds. 

A different method to text generation is the Neural Probabilistic Language Model, specifically Bengio’s model. (VERY) Simply put, this model essentially generalizes the inefficient n-gram model that the Markov chain prediction relies on. By mapping similar words in the corpus to similar vectors the model can eliminate large sections of the data that took so long to calculate with the n-gram Markov model and thus this model functions as a successful text generator. 

In some of the most advanced models, the N-gram model is entirely surpassed. Whereas in most N-gram models, the smallest atomic unit is a single word and there is no notion of similarity between words, the vector word model considers words as vectors that can be similar in meaning and structure to other words. These vector’s dimensions store data about meaning and use. For example the vector representing the word King stores its meaning in such a way that if you were to subtract the vector for the word Man and add the vector for Woman the closest resultant vector would be for the word Queen (Mikolov T. et al.). In this way, the model stores the meaning behind each word and its connection to every other word. Not only do these models store meaning but they also store syntaxical data. For example the vector for apple minus the vector for apples will give a similar vector to the vector for car minus the vector for cars meaning the information about singularity and plurality is also stored in these vectors (Mikolov T. et al.).




Conclusion 
----





References 
----
Stanley F. Chen and Joshua Goodman. 1996. An Empirical Study of Smoothing Techniques for Language Modeling. In 34th Annual Meeting of the Association for Computational Linguistics, pages 310–318, Santa Cruz, California, USA. Association for Computational Linguistics.
https://medium.com/@kpradyumna/understanding-and-implementing-transformer-based-language-models-and-their-variants-cb02f4cbbf17

Mikolov T. https://aclanthology.org/N13-1090/



