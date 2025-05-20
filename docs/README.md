Modern Text Prediction with Century Old Techniques
Introduction 
===

As the title suggests the goal of this experiment was to recreate text predictions similar to the suggested words one might see when typing on an iPhone keyboard by implementing Markov Chains. The Markov Chains were implemented using the C++ programming language with the short story _The Metamorphosis_ by Franz Kafka as a corpus. The decision to use second order Markov Chains to reduce the computational power needed to run the experiment limits it to a purely academic exercise. In this document the theory of Markov Chains and their assumptions will be discussed, then the data methodology used when conducting the experiment will be examined, later the results and expected results will be discussed and compared to modern text prediction algorithms specifically Bengio’s algorithm and finally a conclusion on the significance of the experiment will be produced.

Theory
===

The Markov Chain discovered by Andrey Markov in the early 20th century is an essential analytical device for statistical observations. Markov uncovered the Markov chain whilst settling a disagreement about the assumptions needed in a statistical test. 

A Markov Chain is a grouping of states with different transitions between each state where the transitions occur depending on their associated probabilities.
An example:
Imagine Dany is deciding which candy he wants to eat from his backpack. In his bag Dany has Jolly Ranchers (J), Candy Corn (C) and a Sour Keys(S). After quizzing Dany we find out that after having a Jolly Rancher there is a 20% Dany has another Jolly Rancher, a 70% he has a Candy Corn and a 10% he has a sour key. After more quizzing we are able to make a chart.

![image](https://github.com/user-attachments/assets/fe387164-b452-4aff-b038-cd7a31aa16f5)

From this chart it is clear to see what the chances are that Dany chooses any given candy depending on what candy he has just had, this brings us to our fist important quality of the Markov Chain.

For the Markov Chain to function there is a key assumption and that is that the Markov Chain is a memoryless function. Similar to the Geometric and Exponential distributions, the memoryless property of the Markov Chain implies that the probability of any given future state depends solely on the present state and not the states before it. 


If we look back to Dany and his candy this property can be demonstrated as follows:
3 days ago Dany had a Candy Corn, 2 days ago Dany had a sour key, 1 day ago Dany had a sour key, today Dany had a Jolly Rancher, what is the most likely candy for tomorrow? Now knowing the memoryless property it is easy to see that Dany’s candy choice tomorrow is solely dependent on the probabilities leaving the Jolly Rancher IE: Dany is most likely to have a Candy Corn with a 70% chance of it occurring. 

This is the case for a first order Markov chain where only the most recent event dictates the future state and all other states are ignored due to the memoryless property. In a second order Markov chain the first and the second state dictate the next state while the other states are ignored.

This example paired with an understanding of basic probabilities allow the following formula to be formulated.


“The Markov Property
For any positive integer n and possible states i0,i1,...,in of the random variables,
```math
P(X_n = i_n \mid X_{n-1} = i_{n-1}) = P(X_n = i_n \mid X_0 = i_0, X_1 = i_1, \ldots, X_{n-1} = i_{n-1}).
```
(1)
 

This reconfirms what was previously stated in saying that the next state Xn only depends on the previous state Xn-1 and not every preceding state. The memoryless property is incredibly significant for simplifying calculations and when gathering data. Needing only to get the information of the current state is much more efficient than gathering data of all previous states.

The other significant property of the Markov Chain is the ability to form a transition matrix. A transition matrix is a matrix composed of probabilities of changing from one state to another. Using the matrix allows for computational speeds to be increased. To form the matrix, simply take the outgoing probabilities for each state and fill them into individual rows.
|       | J        | S        | C        |
|-------|----------|----------|----------|
| **J** | P(J→J)   | P(J→S)   | P(J→C)   |
| **S** | P(S→J)   | P(S→S)   | P(S→C)   |
| **C** | P(C→J)   | P(C→S)   | P(C→C)   |

|       | J     | S     | C      |
|-------|-------|-------|--------|
| **J** | 0.2   | 0.1   | 0.7    |
| **S** | 0.4   | 0.6   | 0.0    |
| **C** | 0.15  | 0.8   | 0.05   |





Using the properties of matrices and transitions matrices we can find what is called the two step matrix or P2. This matrix simply represents the probabilities of where we would end up after two choices. To find this matrix simply multiply the transition matrix by itself.

P x P= 
|       | J      | S      | C      |
|-------|--------|--------|--------|
| **J** | 0.185  | 0.175  | 0.640  |
| **S** | 0.3575 | 0.1075 | 0.535  |
| **C** | 0.320  | 0.280  | 0.400  |





This table says that if Dany had a Jolly Rancher yesterday and now he's going to have two candies today the odds of the 2nd candy being a Jolly Rancher is .185 of being a Sour Key is .175 and so on. Using this property if the steps are increased to infinity you can find the probability of being in any state. This is one of the possible methods of evaluating the second order Markov Chain but not without its downsides, large matrix multiplication requires exponentially more calculations.


Data methodology 
===
For the case of our code, n-grams are used to predict the future words. N-grams represent the amount of adjacent words used to predict future text. When n=1 the prediction relies on one sole word, when n=2 (a bi-gram) the prediction relies on the current word and one prior word, when n=5 the prediction uses the current word and the previous four words and so on.  Our code uses bi-grams due to their drastic improvement over 1-gram but reasonable computational demands. To simplify the model, capitalization and punctuation were ignored. 

The transition matrix has a bigram for each row and a single word for each column. Each probability represents the transition from the bigram to the next single word. Instead of generating a second order transition matrix by multiplying a first order matrix by itself, as large matrix multiplications are highly computationally expensive, this project followed another procedure.To generate the transition matrix from the corpus, the program first creates a list of each bigram. For each one of these bigrams, the program looks at the single word that follows. It then counts the number of times each word follows the bigram in the entire corpus and divides by the number of total occurrences of any single word after the bigram. This creates the probability of the next single word given it is preceded by the bigram. This process generates a row of the transition matrix and is repeated for every bigram to populate the entire matrix. Additionally as a smoothing technique, the program generates an 1-gram transition matrix for when a bigram that is not in the corpus is inputted for text generation. 

The second program uses the transition matrix and an inputted bigram to generate a next word. First the program searches for the bigram through each row of the transition matrix. Once it finds the correct bigram it loads the corresponding row into memory. It loads the probability for each possible word then selects the corresponding word based on the distributed probabilities. If the inputted bigram is not in the corpus it will not be in the transition matrix so the program goes back to the 1-gram matrix. To generate the next word, it cuts the inputted bigram into an 1-gram by removing the previous word and only keeping the last word. It then follows the same procedure to find the single word.
When generating multiple words and using the last two generated words as the next bigram, there is a risk that the outputs get stuck in an infinite loop. To avoid this, the code was adapted to randomly pick between the words using their probabilities (Probability Mass Function). This ensures that generated text does not get stuck in a loop.

After writing the text generator code manually, it was discovered that it would take hours to generate long sentences and paragraphs. To optimize the existing text generation code, ChatGPT was used to edit some of the components of the program whilst keeping the general format and structure based on the manually written code.

Discussion
===

An example of generated text: 

```
How many words do you want to generate? 50
Enter the first two words: Gregor did
Gregor did get completely satisfactory compensation because every day the entire stairwell now unfortunately this flight of the enormous brown splotch on the left mr manager to go to the boss because the milk standing not indeed from any lack of hunger and would have to keep the room first while grete
```

Despite randomly choosing the next word based on probabilities instead of always selecting the most probable word, the text generator will still sometimes get stuck in a loop:

```
own chairs the father leaned against the door to the side caught sight of which he spent partly in a high pitched raw voice oh god oh god oh god oh god oh god oh god oh god oh god oh god oh god oh god oh god oh 
```

Additionally, because the corpus is only a short story and the protagonist’s name is frequently repeated in the story, the model produces text with a high density of the word “Gregor”.

```
that gregor must get into his room people had shown her there and without anyone demanding it from its position his mother to do even more terrifying so that he would not have to go back to his sister because she happened to me about that but you mr manager come in but gregor thought about at first he wanted to visit gregor but his sister
```
The technique used to generate the transition matrix is limited as its memory usage increases very quickly with the size of the corpus. This limited the corpus to being only the length of a short story. Having a larger corpus and including different varieties of texts would have made the model more dynamic in its generated text.

Over 1000 words were generated with a variety of different starting words and for the most part the results were similar in quality. To evaluate the quality of these results several phrases were measured using Readable.com, the scores were in the E or lower level indicating that they were almost completely illegible, modern tools like ChatGPT consistently score at the highest possible level. 

These results of the text generation are clearly lacking in quality. There are a few possible reasons for this failure in the program. The Markov chains used are only second order and thus only account for the past two words to predict the third word that comes along. This method may work in other scenarios but with an understanding of the complexity of language it is clear that this result is expectedly poor. Increasing the order of the Markov Chain will likely provide better clarity in the generated text.


An example of what was done in this experiment can be found from the following.

Imagine a text was weighed for its probability and gives a result that the word _red_ is most likely to come after _colour_. In a scenario where the previous two words are _favourite colour_ it is likely that the generated text will have some coherency: 

```
Bob’s favourite colour red
```

However in a longer more complicated situation the generator will fail:
```
Bob says he loves blue like the ocean, that's why Bob’s favourite colour red
```
Not only does it sound like a caveman but the generator is lacking context to make an appropriate prediction of the next word. 

This example clearly illustrates why increasing the order of the Markov chain proves so significant. The more the order is increased the more context the text generator has available and thus it can make a more accurate prediction. So this begs the question, when does the order become substantial to generate text. 

A study in the 90s by Stanley F. Chen and Joshua Goodman found that after 5 N-grams there was a big plateau in improvement to the perplexity (cross-entropy) of the text (2). Cross-entropy measures the difference between the probability distribution of words in the output and in the corpus and gives a reference for accuracy of the model. This becomes a problem. The plateau that is reached at 5-grams can provide good text on a short sentence scale but will still frequently provide text that is incoherent and caveman-ish in longer discourses. If there was unlimited information, time and money the obvious answer is to keep pushing the N-grams despite the aggressive plateau but in the real world this is impractical. It is exponentially more computationally expensive each time the N-gram is increased due to needing to count all the N-1 chains of words. The other reason it is practically impossible is because even with the internet’s incredible size there is a point at which there is not enough data for certain n-grams, take the 50th n-gram for example, to make a successful generator there needs to be reliable counts for every 49-word context, this is not likely to be found even on big internet corpora. 

To improve the poor results, smoothing can be implemented. Smoothing is a method to help reduce the loss of information with unlikely events. In the corpus it is entirely likely that certain combinations of words will never show up. When there are chains missing, the code assigns a probability of zero to that n-gram. With a probability of zero, the multiplication to create a higher order matrix removes information. The aim of smoothing is to bring small amounts of probability to the unlikely events. In our code smoothing is implemented as explained in the Data Methodology section. More advanced techniques could lead to an improvement in performance without a significant increase in computational demands. 

#### A comparison:

Despite shortcomings in Markov text generation, other models are able to accurately generate coherent text.

A different method to text generation is the Neural Probabilistic Language Model, specifically Bengio’s model. Simply put, this mode generalizes the inefficient n-gram model that the Markov chain prediction relies on by mapping similar words in the corpus to similar vectors so the model can eliminate large sections of the data that take long to calculate with the n-gram Markov model and thus this model functions as a successful text generator. (3) Whereas in most n-gram models, the smallest atomic unit is a single word and there is no notion of similarity between words, the vector word model considers words as vectors that can be similar in meaning and in structure to other words. These vector’s dimensions store data about meaning and use. For example the vector representing the word King stores its meaning in such a way that if you were to subtract the vector for the word Man and add the vector for Woman the closest resultant vector would be for the word Queen (4). In this way, the model stores the meaning behind each word and its connection to every other word. Not only do these models store meaning but they also store syntaxical data. For example the vector for apple minus the vector for apples will give a similar vector to the vector for car minus the vector for cars meaning the information about singularity and plurality is also stored in these vectors.




Conclusion 
===
Markov Chains do not provide an adequate method for predicting text due to the high computational demands and lack of sufficiently large corpuses at high n-gram levels. To create an accurate model for text generation, different models are required such as the Bengio model or other large language models. This experiment demonstrates how century-old prediction methods lay a foundation for modern language generation and are essential for modern understanding but real world applications require deeper understanding of semantic fields.
