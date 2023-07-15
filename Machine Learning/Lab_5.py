import pandas as pd
import numpy as np
import string
from collections import Counter


def count_frequency(documents):
    """
    count occurrence of each word in the document set.
    Inputs:
    - documents: list, each entity is a string type SMS message
    Outputs:
    - frequency: a dictionary. The key is the unique words, and the value is the number of occurrences of the word
    """

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)***** 

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return frequency



def create_training_test_sets():

    from sklearn.model_selection import train_test_split

    # learn to read API documentation
    # you can get detailed instructions about this method through this link:
    # https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html

    import urllib.request
    import shutil

    url = 'https://www.cs.uic.edu/~zhangx/teaching/SMSSpamCollection.dat'
    file_name = 'SMSSpamCollection.dat'
    with urllib.request.urlopen(url) as response, open(file_name, 'wb') as out_file:
        shutil.copyfileobj(response, out_file)

    df = pd.read_csv(file_name,
                        sep='\t',
                        header=None,
                        names=['label', 'sms_message'])
    df.head()
    df['label'] = df.label.map({'ham':0, 'spam':1})
    df.head()

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return X_train, X_test, y_train, y_test

def train_NB_model(X_train, y_train):
    """
    training a naive bayes model from the training data.
    Inputs:
    - X_train: an array of shape (num_train,) which stores SMS messages. each entity is a string type SMS message
    - y_train: an array of shape (num_train,). the ground true label for each training data.
    Output:
    - prior: a dictionary, whose key is the class label, and value is the prior probability.
    - conditional: a dictionary whose key is the class label y, and value is another dictionary.
                   In the latter dictionary, the key is word w, and the value is the
                   conditional probability P(X_i = w | y).
    """

    # To make your code more readable, you can implement some auxiliary functions
    # such as `prior_prob` and `conditional_prob` outside of this train_NB_model function

    # compute the prior probability
    prior = prior_prob(y_train)
    
    # compute the conditional probability
    conditional = conditional_prob(X_train, y_train)

    return prior, conditional


def add_smooth(count_x, count_all, alpha=1.0, N=20000):

    """
    compute the conditional probability for a specific word
    Inputs:
    - count_x: the number of occurrence of the word
    - count_all: the total number of words
    - alpha: smoothing parameter
    - N: the number of different values of feature x
    Outputs:
    - prob: conditional probability
    """
    return (count_x + alpha) / (count_all + N*alpha)


def prior_prob(y_train):
    """
    compute the prior probability
    Inputs:
    - y_train: an array that stores ground true label for training data
    Outputs:
    - prior: a dictionary. key is the class label, value is the prior probability.
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****   

    return prior


def conditional_prob(X_train, y_train):
    """
    compute the conditional probability for a document set
    Inputs:
    - X_train: an array of shape (num_train,) which stores SMS messages. each entity is a string type SMS message
    - y_train: an array of shape (num_train,). the ground true label for each training data.
    Ouputs:
    - cond_prob: a dictionary. key is the class label, value is a dictionary in which the key is word, the value is the conditional probability of feature x_i given y.
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return cond_prob




def predict_label(X_test, prior_prob, cond_prob):
    """
    predict the class labels for the testing set
    Inputs:
    - X_test: an array of shape (num_test,) which stores test data. 
              Each entity is a string type SMS message.
    - prior_prob: a dictionary which stores the prior probability for all categories
              We previously used "prior_prob" as the name of function.  
              Here it is used as a dictionary name.  No confusion should arise.
    - cond_prob: a dictionary whose key is the class label y, and value is another dictionary.
                   In the latter dictionary, the key is word w, and the value is the
                   conditional probability P(X_i = w | y).
    Outputs:
    - predict: an array that stores predicted labels
    - test_prob: an array of shape (num_test, num_classes) which stores the posterior probability of each class
    """
    from scipy.special import softmax
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return predict, test_prob

def compute_test_prob(word_count, prior_cat, cond_cat):
    """
    predict the class label for one test example
    Inputs:
    - word_count: a dictionary which stores the frequencies of each word in a SMS message. 
                  Key is the word, value is the number of its occurrence in that message
    - prior_cat: a scalar. prior probability of a specific category
    - cond_cat: a dictionary. conditional probability of a specific category
    Outputs:
    - prob: discriminant value g_y of a specific category for the test example 
                  (no need of normalization, i.e., not exactly the posterior probability)
    """

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return prob

def compute_metrics(y_pred, y_true):
    """
    compute the performance metrics
    Inputs:
    - y_pred: an array of predictions
    - y_true: an array of ground true labels
    Outputs:
    - acc: accuracy
    - cm: confusion matrix
    - f1: f1_score
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return acc, cm, f1
