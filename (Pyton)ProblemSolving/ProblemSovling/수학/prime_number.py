def nats(n):
    yield n
    yield from nats(n+1)


def sieve(s=nats(2)):
    n = next(s)
    print("n", n)
    yield n
    for i in s:
        print(i)
    yield from sieve(i for i in s if i % n != 0)


p = sieve()
