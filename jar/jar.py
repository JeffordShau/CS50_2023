class Jar:
    def __init__(self, capacity=12):
        if capacity > 12:
            capacity = 12
        elif capacity < 0:
            raise ValueError
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        self._size += n
        if self._size > self._capacity:
            raise ValueError

    def withdraw(self, n):
        self._size -= n
        if self._size < 0:
            raise ValueError

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))
    # jar.withdraw(2)
    # jar.deposit(14)



main()