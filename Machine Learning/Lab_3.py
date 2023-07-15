
import numpy as np
np.random.seed(1)

#Problem1


#Problem 1.1
#Problem 1.1-step1
np.random.seed(1)
def euclidean_dist(X_test, X_train):
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    dists = np.add(np.sum(X_test ** 2, axis=1, keepdims=True), np.sum(X_train ** 2, axis=1, keepdims=True).T) - 2* X_test @ X_train.T
  
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return dists

#Problem 1.1-step2
def find_k_neighbors(dists, Y_train, k):
    """
    find the labels of the top k nearest neighbors

    Inputs:
    - dists: distance matrix of shape (num_test, num_train)
    - Y_train: A numpy array of shape (num_train) containing ground true labels for training data
    - k: An integer, k nearest neighbors

    Output:
    - neighbors: A numpy array of shape (num_test, k), where each row containts the 
                labels of the k nearest neighbors for each test example
    """
    num_test = dists.shape[0]
    neighbors = np.zeros((num_test, k))
    sorted_idx = dists.argsort(axis=1)
    for i in range(num_test):
        neighbors[i] = Y_train[sorted_idx[i][:k]]

    return neighbors

    #Problem 1.1-step3
def knn_predict(X_test, X_train, Y_train, k):
    """
    predict labels for test data.

    Inputs:
    - X_test: A numpy array of shape (num_test, dim_feat) containing test data.
    - X_train: A numpy array of shape (num_train, dim_feat) containing training data.
    - Y_train: A numpy array of shape (num_train) containing ground true labels for training data
    - k: An integer, k nearest neighbors

    Output:
    - Y_pred: A numpy array of shape (num_test). Predicted labels for the test data.
    """
    num_test = X_test.shape[0]
    Y_pred = np.zeros(num_test, dtype=int)
    dists = euclidean_dist(X_test, X_train)
    neighbors = find_k_neighbors(dists, Y_train, k)

    for i in range(num_test):
        value, counts = np.unique(neighbors[i], return_counts=True)
        idx = np.argmax(counts)
        Y_pred[i] = value[idx]
    return Y_pred

    
#Problem 1.1-step4
def compute_error_rate(ypred, ytrue):
    """
    Compute error rate given the predicted results and true lable.
    Inputs:
    - ypred: array of prediction results.
    - ytrue: array of true labels.
        ypred and ytrue should be of same length.
    Output:
    - error rate: float number indicating the error in percentage
                    (i.e., a number between 0 and 100).
    """
    error_rate =  (ypred != ytrue).mean()*100

    return error_rate

#Problem 1.2

#Problem 1.2-step1
def split_nfold(num_examples, n):
    """
    Split the dataset in to training sets and validation sets.
    Inputs:
    - num_examples: Integer, the total number of examples in the dataset
    - n: number of folds
    Outputs:
    - train_sets: List of lists, where train_sets[i] (i = 0 ... n-1) contains 
                    the indices of examples for trainning
    - validation_sets: List of list, where validation_sets[i] (i = 0 ... n-1) 
                    contains the indices of examples for validation

    Example:
    When num_examples = 10 and n = 5, 
        the output train_sets should be a list of length 5, 
        and each element in this list is itself a list of length 8, 
        containing 8 indices in 0...9
    For example, 
        we can initialize by randomly permuting [0, 1, ..., 9] into, say,
        [9, 5, 3, 0, 8, 4, 2, 1, 6, 7]
        Then we can have
        train_sets[0] = [3, 0, 8, 4, 2, 1, 6, 7],  validation_sets[0] = [9, 5]
        train_sets[1] = [9, 5, 8, 4, 2, 1, 6, 7],  validation_sets[1] = [3, 0]
        train_sets[2] = [9, 5, 3, 0, 2, 1, 6, 7],  validation_sets[2] = [8, 4]
        train_sets[3] = [9, 5, 3, 0, 8, 4, 6, 7],  validation_sets[3] = [2, 1]
        train_sets[4] = [9, 5, 3, 0, 8, 4, 2, 1],  validation_sets[4] = [6, 7]
    Within train_sets[i] and validation_sets[i], the indices do not need to be sorted.
    """
    # Here is the pseudo code:
    # idx = np.random.permutation(num_examples).tolist() # generate random index list
    # fold_size = num_examples//n   # compute how many examples in one fold.
    #                               # note '//' as we want an integral result
    # train_sets = []
    # validation_sets = []
    # for i = 0 ... n-1
    #	  start = # compute the start index of the i-th fold
    #	  end = # compute the end index of the i-th fold
    #   if i == n-1
    #     end = num_examples  # handle the remainder by allocating them to the last fold
    #   For example, when num_examples = 11 and n = 5, 
    #     fold_size = 11//5 = 2
    #     i = 0: start = 0, end = 2
    #     i = 1: start = 2, end = 4
    #     i = 2: start = 4, end = 6
    #     i = 3: start = 6, end = 8
    #     i = 4: start = 8, end = 11  (take up the remainder of 11//5)
    #
    #   # Now extract training example indices from the idx list using start and end
    #   train_set = idx[`0 to num_example-1` except `start to end-1`]  
    #   train_sets.append(train_set)
    #
    #   # Extract validation example indices from the idx list using start and end
    #   val_set = idx[start to end-1] 
    #   validation_sets.append(val_set)
    #avoid randomness
    np.random.seed(1)
    
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return train_sets, validation_sets

#Problem 1.2-step2
def cross_validation(classifier, X, Y, n, *args):
    """
    Perform cross validation for the given classifier, 
        and return the cross validation error rate.
    Inputs:
    - classifier: function of classification method
    - X: A 2-D numpy array of shape (num_train, dim_feat), containing the whole dataset
    - Y: A 1-D numpy array of length num_train, containing the ground-true labels
    - n: number of folds
    - *args: parameters needed by the classifier.
            In this assignment, there is only one parameter (k) for the kNN clasifier.
            For other classifiers, there may be multiple paramters. 
            To keep this function general, 
            let's use *args here for an unspecified number of paramters.
    Output:
    - error_rate: a floating-point number indicating the cross validation error rate
    """
    # Here is the pseudo code:
    # errors = []
    # size = X.shape[0] # get the number of examples
    # train_sets, val_sets = split_nfold(size, n)  # call the split_nfold function
    #
    # for i in range(n):
    #   train_index = train_sets[i]
    #   val_index = val_sets[i]
    #   # get the training and validation sets of input features from X
    # 	X_train, X_val = X[...], X[...] 
    #
    #   # get the training and validation labels from Y
    # 	y_train, y_val = Y[...], Y[...] 
    #
    #   # call the classifier to get prediction results for the current validation set
    # 	ypred = # call classifier with X_val, X_train, y_train, and *args
    #                                   
    # 	error = # call compute_error_rate to compute the error rate by comparing ypred against y_val
    # 	append error to the list `errors`
    # error_rate = mean of errors
    np.random.seed(1)
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return error_rate 


#Problem2
def problem2():
    """
    copy your solutions of problem 2 to this function
    DONOT copy the code for plotting 

    Outputs:
    - error_rates: A numpy array of size (len(trials_size),) which store error rates for different example size
    - cverror_rates: A numpy array of size (len(trials_fold),) which store error rates for different fold size
    """
    import os
    import gzip

    DATA_URL = 'http://yann.lecun.com/exdb/mnist/'

    # Download and import the MNIST dataset from Yann LeCun's website.
    # Each image is an array of 784 (28x28) float values  from 0 (white) to 1 (black).
    def load_data():
        x_tr = load_images('train-images-idx3-ubyte.gz')
        y_tr = load_labels('train-labels-idx1-ubyte.gz')
        x_te = load_images('t10k-images-idx3-ubyte.gz')
        y_te = load_labels('t10k-labels-idx1-ubyte.gz')

        return x_tr, y_tr, x_te, y_te

    def load_images(filename):
        maybe_download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=16)
        return data.reshape(-1, 28 * 28) / np.float32(256)

    def load_labels(filename):
        maybe_download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=8)
        return data

    # Download the file, unless it's already here.
    def maybe_download(filename):
        if not os.path.exists(filename):
            from urllib.request import urlretrieve
            print("Downloading %s" % filename)
            urlretrieve(DATA_URL + filename, filename)

    Xtrain, ytrain, Xtest, ytest = load_data()

    train_size = 10000
    test_size = 10000

    Xtrain = Xtrain[0:train_size]
    ytrain = ytrain[0:train_size]

    Xtest = Xtest[0:test_size]
    ytest = ytest[0:test_size]

    # problem 2.1
    size = 1000
    k = 1
    # Here is the pseudo code:
    #
    # get the feature/label of the first 'size' (i.e., 1000) number of training examples
    # cvXtrain = Xtrain[...]  
    # cvytrain = ytrain[...]  

    # trial_folds   = [3, 10, 50, 100, 1000]
    # trials = # number of trials, i.e., get the length of trial_sizes
    # cverror_rates = [0]*trials

    # for t = 0 ... trials-1
    # 	error_rate = # call the 'cross_validation' function to get the error rate 
    #                #  for the current trial (of fold number)
    # 	cverror_rates[t] = error_rate
    #
    #   # print the error rate for the current trial.
    # 	print('{:d}-folds error rate: {:.2f}%\n'.format(trial_folds[t], error_rate)) 
    #
    # plot the figure:
    # f = plt.figure()
    # plt.plot(...)
    # plt.xlabel(...)
    # plt.ylabel(...)
    # plt.show()

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****


    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return cverror_rates

# Problem 3
def problem3():
    """
    copy your solutions of problem 3 to this function.
    DONOT copy the code for plotting 
    
    Outputs: 
    - err_ks: A numpy array of size (len(list_ks),) which store error rate for each k
    - best_k: An integer which gives lowest error rate on validation set
    - err_test: Error rate on test set
    - cm: confusion matrix
    """
    from sklearn.datasets import load_iris
    from sklearn.model_selection import train_test_split

    # loading iris dataset
    iris = load_iris()
    # split dataset into training set and test set
    X_train, X_test, Y_train, Y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=1)

    # problem 3.1
    # Here is the pseudo code:
    # list_ks = 1,2,...,100
    # err_ks = 1D array of length 100
    # for k in list_ks:
    #   err_ks[k-1] = cross_validation under k 
    # best_k = argmin(err_ks)+1
    # plot err_ks versus list_ks

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # problem 3.2
    # Here is the pseudo code:
    # y_pred = knn_predict on X_test using X_train, Y_train, and best_k
    # use compute_error_rate to compute the error of y_pred compared with Y_test
    # Print the error rate with a line like 'The test error is x.y%'


    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    
    # problem 3.3
    nclass = len(np.unique(Y_test))  # should be 3. Just be more adaptive to data.
    cm = np.zeros((nclass, nclass), dtype=int)  # confusion matrix is integer valued

    # Here is the pseudo code for Task 1: 
    # for t = 0...nte-1  # nte is the number of test examples
    #    cm[c1, c2] += 1  # c1 and c2 corresponds to the class of the t-th test example
    #                     # according to Y_test and y_pred, respectively
    #
    # Here is the pseudo code for Task 3:
    # Well, please consult the textbook, as I really hope you can do it yourself,
    # especially when the right answer is provided by sklearn for comparison


    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return err_ks, best_k, err_test, cm, cr, f1



    

