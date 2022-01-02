'''
author: Naachiket Pant
email: naachiketpant88@gmail.com
date: 02-01-2022
description: This is the main pine file

'''
import sys
from Stack import Stack

running = True


def precedence(n):
    if n == '^':
        return 3
    if n == '/' or n == '*':
        return 2
    elif n == '+' or n == '-':
        return 1
    return 0

def infixToPostfix(infix:str): 
    stack = Stack()
    stack.stk = []
    stack.t = -1
    postfix = []

    i = 0
    while i < (len(infix)):
        ch = infix[i]
        if ch.isspace():
            continue
        if ch.isdecimal():
            tempNumber = ''
            while i < len(infix) and infix[i].isdecimal():
                tempNumber = tempNumber + infix[i]
                i+=1
            postfix.append(tempNumber)
            continue
             
        elif ch == '(':
            stack.push(ch)
        elif ch == ')':
            while not stack.isEmpty() and stack.top() != '(':
                postfix.append(stack.top())
                stack.pop()

            stack.pop() #popping (
        else:
            while not stack.isEmpty() and precedence(ch) <= precedence(stack.top()):
                postfix.append(stack.top())
                stack.pop()
                
            stack.push(ch)

        i += 1

    while not stack.isEmpty():
        postfix.append(str(stack.top()))
        stack.pop()
    return postfix

#CALCULATE VALUE OF EXPRESSION
def calculateValueFromPostfix(exp):
    stack = Stack()
    stack.stk = []
    stack.t = -1
    for i in exp:
        if i.isdecimal():
            stack.push(i)
        else:
            operator = i
            op1 = stack.top()
            stack.pop()
            op2 = stack.top()
            stack.pop()
            expression = str(op2) + operator + str(op1)
            stack.push(eval(expression))

    return stack.top()

#MAIN LOOP
while running:
    print("pine> ", end = '')
    exp = input()
    
    #Check for exit 
    if exp == 'exit' or exp == 'bye':
        print("Thanks for using pine!")
        exit(0)

    #Evaluating expressions
    postfix = infixToPostfix(exp)
    ans = calculateValueFromPostfix(postfix)

    print(ans)
