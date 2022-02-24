from typing import List, Tuple


class Skill:
    def __init__(self, name: str, level: str):
        self.name = name
        self.level = int(level)

    def __str__(self) -> str:
        return f"Skill({self.name}, {self.level})"

    def __repr__(self):
        return self.__str__()


class Contributor:
    def __init__(self, name: str, skills: List[Skill]):
        self.name = name
        self.skills = skills

    def __str__(self) -> str:
        return f"Contributor({self.name}, {self.skills})"

    def __repr__(self):
        return self.__str__()


class Project:
    def __init__(self, name: str, days_to_complete: str, score: str, best_before: str, roles: List[Skill]):
        self.name = name
        self.days_to_complete = int(days_to_complete)
        self.score = int(score)
        self.best_before = int(best_before)
        self.roles = roles

    def __str__(self) -> str:
        return f"Project({self.name}, {self.days_to_complete}, {self.score}, {self.best_before}, {self.roles})"

    def __repr__(self):
        return self.__str__()


def take_input(path) -> (List[Contributor], List[Project]):
    with open(path, 'r') as f:
        num_contributors, num_projects = [int(i) for i in f.readline().split()]
        contributors: List[Contributor] = []
        for i in range(num_contributors):
            name, num_skills = f.readline().split()
            num_skills = int(num_skills)
            skills: List[Skill] = []
            for j in range(num_skills):
                skill_name, skill_level = f.readline().split()
                skills.append(Skill(skill_name, skill_level))
            contributors.append(Contributor(name, skills))

        projects: List[Project] = []
        for i in range(num_contributors):
            name, days_to_complete, score, best_before, num_roles = f.readline().split()
            num_roles = int(num_roles)
            roles: List[Skill] = []
            for j in range(num_roles):
                skill_name, skill_level = f.readline().split()
                skills.append(Skill(skill_name, skill_level))
            projects.append(Project(name, days_to_complete, score, best_before, roles))

    return contributors, projects


def solve(contributors: List[Contributor], projects: List[Project]) -> List[Tuple[Project, List[Contributor]]]:
    return [(projects[0], [contributors[0], contributors[1]]), (projects[1], [contributors[0], contributors[2]])]


def run(input_path: str, output_path: str):
    contributors, projects = take_input(input_path)
    result = solve(contributors, projects)
    with open(output_path, 'w') as f:
        f.write(str(len(result)) + "\n")
        for project, participants in result:
            f.write(project.name + "\n")
            for participant in participants:
                f.write(participant.name + " ")
            f.write("\n")


if __name__ == '__main__':
    test_cases = [
        ('inputs/a_an_example.in.txt', 'outputs/a_an_example.out.txt'),
        # ('inputs/b_better_start_small.in.txt', 'outputs/b_better_start_small.out.txt'),
        # ('inputs/c_collaboration.in.txt', 'outputs/c_collaboration.out.txt'),
        # ('inputs/d_dense_schedule.in.txt', 'outputs/d_dense_schedule.out.txt'),
        # ('inputs/e_exceptional_skills.in.txt', 'outputs/e_exceptional_skills.out.txt'),
        # ('inputs/f_find_great_mentors.in.txt', 'outputs/f_find_great_mentors.out.txt')
    ]
    for in_file, out_file in test_cases:
        run(in_file, out_file)
