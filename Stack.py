class Stack:
    t = -1
    stk = []

    def push(self, n):
        self.stk.append(n)
        self.t += 1

    def pop(self):
        if self.isEmpty():
            return -1
        self.stk.pop()
        self.t -= 1

    def display(self):
        print(self.stk)

    def isEmpty(self):
        if self.t == -1:
            return True
        return False
    def top(self):
        if not self.isEmpty():
            return self.stk[self.t]
        return -1
