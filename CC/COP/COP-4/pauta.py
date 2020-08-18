import numpy as np
from scipy.linalg import solve_triangular
dec = lambda num , d: int((num%1)*(10**d)-((num%1)*(10**d))%1)
from ipywidgets import interact

def show_answer(SEED):
    # Loading data
    X1=np.load('data/IML/X1-'+str(SEED)+'.npy')
    Y1=np.load('data/IML/Y1-'+str(SEED)+'.npy')
    X2=np.load('data/IML/X2-'+str(SEED)+'.npy')
    Y2=np.load('data/IML/Y2-'+str(SEED)+'.npy')
    Yt=np.load('data/IML/Yt-'+str(SEED)+'.npy')
    
    # 1.- X1*W1=Y1
    W1=solve_triangular(X1,Y1)
    q1=np.linalg.norm(W1,'fro')
    print('Answer 1: ',dec(q1,5))

    # 2.- W2*X2=Y2, X2.T*W2.T=Y2.T
    W2=solve_triangular(X2.T,Y2.T, lower=True).T
    q2=np.linalg.norm(W2,'fro')
    print('Answer 2: ',dec(q2,5))

    # 3.- P_{y01}(X) = Y_1\,(X-X_2)\,(X_1-X_2)^{-1}+Y_2\,(X-X_1)\,(X_2-X_1)^{-1}
    #       P_{y01}(0) = -Y_1 X_2,(X_1-X_2)^{-1} - Y_2 X_1 (X_2-X_1)^{-1}
    #       P_{y01}(0) = (-Y_1 X_2 + Y_2 X_1) (X_1-X_2)^{-1}
    #       W (X_1-X_2) = (-Y_1 X_2 + Y_2 X_1)
    #       (X_1-X_2).T W.T = (-Y_1 X_2 + Y_2 X_1).T
    A = (X1-X2)
    B = (-np.dot(Y1,X2)+np.dot(Y2,X1))
    P = solve_triangular(A.T, B.T, lower=True).T
    q3=np.linalg.norm(P,'fro')
    print('Answer 3: ',dec(q3,5))

    # 4.- P_{y01}(X)=Y_1\,(X-X_2)\,(X_1-X_2)^{-1}+Y_2\,(X-X_1)\,(X_2-X_1)^{-1}
    # D = X_1-X_2
    #       Yt = Y_1\,(X-X_2)\,D^{-1} - Y_2\,(X-X_1)\,D^{-1}
    #       Yt D = Y_1 (X-X_2) - Y_2 (X-X_1)
    #       Yt D = Y_1 X - Y_1 X_2 - Y_2 X + Y_2 X_1
    #       Yt D + Y_1 X_2 - Y_2 X_1 = (Y_1 - Y_2) X
    D = X1-X2
    A = (Y1-Y2)
    B = np.dot(Yt,D)+np.dot(Y1,X2)-np.dot(Y2,X1)
    X = solve_triangular(A, B, lower=False)
    q4=np.linalg.norm(X,'fro')
    print('Answer 4: ',dec(q4,5))

interact(show_answer, SEED=[0,1,3,4,5,6,7,8])
