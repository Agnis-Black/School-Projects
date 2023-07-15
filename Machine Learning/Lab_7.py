import numpy as np
import matplotlib.pyplot as plt


np.random.seed(1)


#Problem 1.2
def sigmoid(z):
    """
    sigmoid function that maps inputs into the interval [0,1]
    Your implementation must be able to handle the case when z is a vector (see unit test)
    Inputs:
    - z: a scalar (real number) or a vector
    Outputs:
    - trans_z: the same shape as z, with sigmoid applied to each element of z
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return trans_z

def logistic_regression(X, w):
    """
    logistic regression model that outputs probabilities of positive examples
    Inputs:
    - X: an array of shape (num_sample, num_features)
    - w: an array of shape (num_features,)
    Outputs:
    - logits: a vector of shape (num_samples,)
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return logits

#Problem 1.3
def logistic_loss(X, w, y):
    """
    a function that compute the loss value for the given dataset (X, y) and parameter w;
    It also returns the gradient of loss function w.r.t w
    Here (X, y) can be a set of examples, not just one example.
    Inputs:
    - X: an array of shape (num_sample, num_features)
    - w: an array of shape (num_features,)
    - y: an array of shape (num_sample,), it is the ground truth label of data X
    Output:
    - loss: a scalar which is the value of loss function for the given data and parameters
    - grad: an array of shape (num_featues,), the gradient of loss 
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return loss, grad

#Problem 2.5
def train_model_gd():
    import numpy as np
    import matplotlib.pyplot as plt
    from sklearn.datasets import load_digits
    from sklearn.model_selection import train_test_split

    np.random.seed(1)

    # load the digits dataset
    digits = load_digits(n_class=2)
    ones = np.ones(digits.data.shape[0]).reshape(-1, 1)
    digits.data = np.concatenate((ones, digits.data), axis=1)
    from sklearn.preprocessing import StandardScaler

    

    X_train, X_test, y_train, y_test = train_test_split(digits.data, digits.target, train_size=0.8, random_state=1)
    sc = StandardScaler()
    sc.fit(X_train)
    X_train = sc.transform(X_train)
    X_test = sc.transform(X_test)

    num_iters = 200
    lr = 0.1

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return acc

#Problem 3
def softmax(x):
    """
    Convert logits for each possible outcomes to probability values.
    In this function, we assume the input x is a 2D matrix of shape (num_sample, num_classes).
    So we need to normalize each row by applying the softmax function.
    Inputs:
    - x: an array of shape (num_sample, num_classse) which contains the logits for each input
    Outputs:
    - probability: an array of shape (num_sample, num_classes) which contains the
                    probability values of each class for each input
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return probability

def MLR(X, W):
    """
    performs logistic regression on given inputs X
    Inputs:
    - X: an array of shape (num_sample, num_feature)
    - W: an array of shape (num_feature, num_class)
    Outputs:
    - probability: an array of shape (num_sample, num_classes)
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return probability

#Problem 3.1
def cross_entropy_loss(X, W, y):
    """
    Inputs:
    - X: an array of shape (num_sample, num_feature)
    - W: an array of shape (num_feature, num_class)
    - y: an array of shape (num_sample,)
    Ouputs:
    - loss: a scalar which is the value of loss function for the given data and parameters
    - grad: an array of shape (num_featues, num_class), the gradient of the loss function 
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return loss, grad

#Problem 3.2
def learn_real_dataset():
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****



    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return acc