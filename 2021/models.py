from typing import List, Dict


class Street:

    def __init__(self, b: int, e: int, name: str, distance: int):
        self.start = b
        self.end = e
        self.name = name
        self.distance = distance

    def __repr__(self):
        return f"({self.start}, {self.end}, {self.name}, {self.distance}"


class Car:

    def __init__(self):
        self.streets: List[Street] = []

    def __repr__(self):
        return f"streets {self.streets.__repr__()}"


class Simulation:

    def __init__(self, file: str):
        with open(file, 'r') as f:
            lines = f.readlines()
            self.time, self.intersections, s, v, self.bonus = [int(x) for x in lines[0].split(" ")]
            self.streets: Dict[str, Street] = {}
            self.cars: List[Car] = []
            for idx in range(1, 1+s):
                b, e, name, le = lines[idx].split(" ")
                self.streets[name] = Street(int(b), int(e), name, int(le))
            for idx in range(1+s, 1+s+v):
                strts = lines[idx].split(" ")
                car = Car()
                for street in strts[1:]:
                    car.streets.append(self.streets[street])


simulation = Simulation("/home/shreyansh/Downloads/a.txt")
print(simulation)
