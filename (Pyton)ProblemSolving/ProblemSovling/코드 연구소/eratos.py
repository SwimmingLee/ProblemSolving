import time


def logging_time(original_fn):
    def wrapper_fn(*args, **kwargs):
        start_time = time.time()
        result = original_fn(*args, **kwargs)
        end_time = time.time()
        print("WorkingTime[{}]: {} sec".format(
            original_fn.__name__, end_time-start_time))
        return result
    return wrapper_fn


@logging_time
def primes_gener(max_int):
    return [i for i in get_primes(max_int)]


def get_primes(max_int):
    numbers = range(2, max_int)
    while len(numbers) > 0:
        # only keep numbers that are NOT divisible by the prime
        numbers = [num for num in numbers if num %
                   numbers[0] != 0 or num == numbers[0]]
        yield numbers[0]  # yield the prime
        # make a new numbers-array, the first num is a new prime
        numbers = numbers[1:]


@logging_time
def primes_upto(limit):
    is_prime = [False] * 2 + [True] * (limit - 1)
    for n in range(int(limit**0.5 + 1.5)):  # stop at ``sqrt(limit)``
        if is_prime[n]:
            for i in range(n*n, limit+1, n):
                is_prime[i] = False
    return [i for i, prime in enumerate(is_prime) if prime]


@logging_time
def primes_slice(limit):
    is_prime = [False] * 2 + [True] * (limit - 1)
    for n in range(int(limit**0.5 + 1.5)):  # stop at ``sqrt(limit)``
        if is_prime[n]:
            is_prime[n*n::n] = [False] * ((limit - n*n)//n + 1)
    return [i for i, prime in enumerate(is_prime) if prime]


# print([i for i in get_primes(10000)])
# print(primes_upto(10000))
# print(primes_slice(10000))
# a = [1, 2, 3]
print(enumerate(a))
# primes_gener(100_000)
# primes_gener(100000)
# primes_upto(100_000)
# primes_slice(100_000)
