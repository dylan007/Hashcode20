import os
from typing import List, Dict


class Street:

    def __init__(self, b: int, e: int, name: str, distance: int):
        self.start = b
        self.end = e
        self.name = name
        self.distance = distance
        self.cars: List[Car] = []

    def __repr__(self):
        return f"({self.start}, {self.end}, {self.name}, {self.distance})"


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
                b, e, name, le = lines[idx].strip().split(" ")
                self.streets[name] = Street(int(b), int(e), name, int(le))
            for idx in range(1+s, 1+s+v):
                strts = lines[idx].strip().split(" ")
                car = Car()
                for street in strts[1:]:
                    car.streets.append(self.streets[street])
                    self.streets[street].cars.append(car)
                self.cars.append(car)

    def __repr__(self):
        return "\n".join([i.__repr__() for i in self.cars])


def run(in_path: str, out_path: str):
    simulation = Simulation(in_path)
    intersections: Dict[int, List[Street]] = {}
    for street_name, street in simulation.streets.items():
        intersection = street.end
        if len(street.cars) == 0:
            continue
        if intersection not in intersections:
            intersections[intersection] = []
        intersections[intersection].append(street)

    lines: List[str] = [str(len(intersections))]
    for intersection, streets in intersections.items():
        lines.append(str(intersection))
        lines.append(str(len(streets)))
        for street in streets:
            lines.append(f"{street.name} {min(simulation.time, street.distance, len(street.cars))}")

    with open(out_path, "w") as f:
        for line in lines:
            f.write(line+"\n")


prefix = "out1"
try:
    os.mkdir(prefix)
except Exception:
    pass
for file_name in ["a", "b", "c", "d", "e", "f"]:
    run(f"input/{file_name}.txt", f"{prefix}/{file_name}.txt")
