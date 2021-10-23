import atexit
from hashlib import sha512
import random as _random
import shutil
import subprocess
import sys
import os.path
import yaml

try:
    shutil.rmtree("secret")
    shutil.rmtree("sample")
except FileNotFoundError:
    pass

def samples(**kwargs):
    if "sample" in Subtask.tasks:
        return Subtask.tasks["sample"]
    task = Subtask("sample")
    task.limits = kwargs
    return task


def secret(**kwargs):
    if "secret" in Subtask.tasks:
        return Subtask.tasks["secret"]
    task = Subtask("secret")
    task.limits = kwargs
    return task


def subtask(score, **kwargs):
    task = Subtask(os.path.join("secret", "subtask") + str(Subtask.subtaskName))
    Subtask.subtaskName += 1
    task.score = score
    task.limits = kwargs
    return task


def case(name=None):
    return Subtask.current.case(name)


def use_solution(name):
    Solution.current = Solution(name)
    Solution.current.compile()

class io:
    @staticmethod
    def line(*args):
       io.raw(" ".join(str(x) for x in args) + "\n") 

    @staticmethod
    def raw(s):
        Case.current.write(s)


class numtheory:
    @staticmethod
    def primes(upto):
        isprime = [True] * upto
        primes = []
        for i in range(2, len(isprime)):
            if isprime[i]:
                primes.append(i)
                for j in range(i * i, len(isprime), i):
                    isprime[j] = False
        return primes

    @staticmethod
    def is_prime(n):
        if n==0 or n==1 or n==4 or n==6 or n==8 or n==9:
            return False
        if n==2 or n==3 or n==5 or n==7:
            return True
        s = 0
        d = n-1
        while d%2==0:
            d>>=1
            s+=1
        assert(2**s * d == n-1)
        def trial_composite(a):
            if pow(a, d, n) == 1:
                return False
            for i in range(s):
                if pow(a, 2**i * d, n) == n-1:
                    return False
            return True  
        for i in range(16):
            a = _random.randrange(2, n)
            if trial_composite(a):
                return False
        return True  

    @staticmethod
    def divisors(n):
        return sympy.ntheory.divisors(n)


class graphs:
    @staticmethod
    def tree_random_parent(n, root=None, one_index=False):
        """Generates a tree by going through all vertices in random order, assigning
        as parent a random one of the previous order. This tends to give a small
        height of the tree.

        The tree is rooted if edges are directed in first -> second order.
        """
        off = 1 if one_index else 0
        vs = list(range(n))
        if root is not None:
            assert 0 <= root < n
            vs.pop(root)
        random.shuffle(vs)
        if root is not None:
            vs.insert(0, root)

        eds = []
        for i, a in enumerate(vs[1:]):
            par = vs[random.randint(0, i)]
            eds.append((par + off, a + off))
        return eds

    @staticmethod
    def star(n, middle=None, one_index=False):
        off = 1 if one_index else 0
        if middle:
            assert 0 <= middle < n
        else:
            middle = random.randint(0, n - 1)
        eds = []
        for i in range(n):
            if i != middle:
                eds.append((middle + off, i + off))
        return eds

    @staticmethod
    def uniform_edge(n, m, one_index=False):
        off = 1 if one_index else 0
        all_eds = n * (n - 1) // 2
        if m > all_eds:
            raise Exception("Too many edges {} for graph on {} vertices".format(m, n))
        if m <= all_eds // 2:
            eds = set()
            while len(eds) < m:
                a = random.randint(0, n - 1) + off
                b = random.randint(0, n - 1) + off
                if a > b: a, b = b, a
                if a == b or (a, b) in eds: continue
                eds.add((a, b))
            return eds
        all_eds = [(a + off, b + off) for b in range(n) for a in range(b)]
        return set(random.sample(all_eds, m))


class random:
    @staticmethod
    def seed(s):
        _random.seed(s)

    @staticmethod
    def randint(lo, hi):
        return _random.randint(lo, hi)

    @staticmethod
    def randrange(lo, hi, step=1):
        return _random.randrange(lo, hi, step)

    @staticmethod
    def prime(lo, hi):
        while True:
            l = random.randrange(lo, hi)
            while not numtheory.is_prime(l):
                l += 1
                if l == hi:
                    break
            else:
                return l

    @staticmethod
    def shuffle(l):
        _random.shuffle(l)

    @staticmethod
    def sample(population, k):
        return _random.sample(population, k)


def generator(func):
    def wrapper(*args, **kwargs):
        with case(func.__name__):
            return func(*args, **kwargs)
    return wrapper


class Case:
    current = None

    def __init__(self, path, name):
        self.name = name
        self.path = path
        self.infile = None

    def write(self, val):
        self.infile.write(val)

    def __enter__(self):
        assert not Case.current
        Case.current = self
        self.infile = open(self.path + ".in", "w")
        random.seed(_hash(self.path))
        return self

    def __exit__(self, type, value, traceback):
        self.infile.close()
        if Solution.current and not traceback:
            Solution.current.solve(self.path)
        Case.current = None


class Subtask:
    subtaskName = 1
    caseName = 1
    current = None
    is_scoring = False
    tasks = {}

    def __init__(self, name):
        self.name = name
        self.cases = {}
        self.includes = set()
        self.score = 0
        self.limits = {}

    def case(self, name):
        fullname = "{:03d}".format(Subtask.caseName)
        Subtask.caseName += 1
        if name:
            fullname = fullname + "-" + name
        c = Case(os.path.join(self.name, fullname), fullname)
        self.cases[c.path] = c
        return c

    def include(self, *tasks):
        self.includes.update(tasks)
        return self

    def _do_includes(self):
        for s in self.includes:
            s._do_includes()
            self.cases.update(s.cases)
        s = set()
        for path, case in self.cases.items():
            included_path = os.path.join(self.name, case.name)
            if not os.path.isfile('{}.in'.format(included_path)):
                os.symlink(os.path.relpath('{}.in'.format(path), self.name), '{}.in'.format(included_path))
                os.symlink(os.path.relpath('{}.ans'.format(path), self.name), '{}.ans'.format(included_path))

    def __enter__(self):
        assert not Subtask.current
        assert self.name not in Subtask.tasks
        Subtask.current = self
        if self.score:
            Subtask.is_scoring = True
        os.makedirs(self.name, exist_ok=True)
        return self

    def __exit__(self, type, value, traceback):
        Subtask.current = None
        Subtask.tasks[self.name] = self


class Solution:
    current = None

    def __init__(self, name):
        self.name = name
        self.path = os.path.join("..", "submissions", "accepted", name)

    def compile(self):
        if self.name.endswith(".cpp") or self.name.endswith(".cc"):
            process = subprocess.run(
                    ["g++", "-g", "-Wall", "-o", "sol", "-std=gnu++17", "-fsanitize=undefined,address",
                        self.path],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE)
            if process.returncode != 0:
                print("Failed compiling solution", self.name)
                if process.stdout: print(process.stdout.decode('UTF-8'))
                if process.stderr: print(process.stderr.decode('UTF-8'))
                sys.exit(1)
            atexit.register(lambda: os.remove("sol"))
        else:
            print("Does not know how to compile", self.name)
            sys.exit(1)

    def solve(self, case_path):
        if self.name.endswith(".cpp") or self.name.endswith(".cc"):
            with open(case_path + ".in") as infile:
                with open(case_path + ".ans", "w") as outfile:
                    process = subprocess.run(["./sol"], stdin=infile, stdout=outfile)
                    if process.returncode != 0:
                        print(self.name, "failed solving case", case_path)
                        if process.stderr: print(process.stderr.decode('UTF-8'))
                        sys.exit(1)


def _hash(s):
    h = sha512(s.encode()).digest()
    return int.from_bytes(h, 'big')


@atexit.register
def _write_config():
    config = {}
    score_sum = 0
    for name, task in Subtask.tasks.items():
        task._do_includes()
        if not Subtask.is_scoring and not task.limits:
            continue
        task_config = {
                "grader_flags": "first_error"
        }
        if Subtask.is_scoring:
            task_config["grader_flags"] = "min"
            task_config["range"] = '0 {}'.format(task.score)
            task_config["accept_score"] = task.score
            if task.score:
                task_config["on_reject"] = "break"
                score_sum += task.score
            else:
                task_config["on_reject"] = "continue"
        if task.limits:
            task_config["input_validator_flags"] = ' '.join('{}={}'.format(k, v) for k, v in task.limits.items())
        with open("{}/testdata.yaml".format(name), "w") as config_file:
            yaml.dump(task_config, config_file)

    root_config = {
    }
    secret_config = {
    }
    if Subtask.is_scoring:
        root_config["on_reject"] = "continue"
        root_config["range"] = "0 {}".format(score_sum)
        root_config["grader_flags"] = "ignore_sample"
        secret_config["on_reject"] = "continue"
        secret_config["range"] = "0 {}".format(score_sum)
        secret_config["grader_flags"] = "first_error accept_if_any_accepted"
    with open("testdata.yaml".format(name), "w") as config_file:
        yaml.dump(root_config, config_file)
    with open("secret/testdata.yaml".format(name), "w") as config_file:
        yaml.dump(secret_config, config_file)
