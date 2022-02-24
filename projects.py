from typing import List, Tuple, Dict, Set


class Skill:
    def __init__(self, name: str, level: str):
        self.name = name
        self.level = int(level)

    def __str__(self) -> str:
        return f"Skill({self.name}, {self.level})"

    def __repr__(self):
        return self.__str__()


class Contributor:
    def __init__(self, name: str, skills: Dict[str, Skill]):
        self.name = name
        self.skills = skills
        self.available_at = 0

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
            skills: Dict[str, Skill] = {}
            for j in range(num_skills):
                skill_name, skill_level = f.readline().split()
                skills[skill_name] = Skill(skill_name, skill_level)
            contributors.append(Contributor(name, skills))

        projects: List[Project] = []
        for i in range(num_projects):
            name, days_to_complete, score, best_before, num_roles = f.readline().split()
            num_roles = int(num_roles)
            roles: List[Skill] = []
            for j in range(num_roles):
                skill_name, skill_level = f.readline().split()
                roles.append(Skill(skill_name, skill_level))
            projects.append(Project(name, days_to_complete, score, best_before, roles))

    return contributors, projects


def project_score(project: Project) -> int:
    return project.score


# returns leftmost element with key
def bin_search(people: List[Contributor], key: int, skill_name: str) -> int:
    left: int = 0
    right: int = len(people) - 1
    while left <= right:
        # print('lr', left, right)
        mid = (left + right) // 2
        skill = people[mid].skills[skill_name].level
        if skill < key:
            left = mid + 1
        elif (skill > key and mid > left) or \
                (skill == key and mid > 0 and skill == people[mid-1].skills[skill_name].level):
            right = mid - 1
        else:
            return mid
    return len(people)


def solve(contributors: List[Contributor], projects: List[Project]) -> List[Tuple[Project, List[Contributor]]]:
    projects = sorted(projects, key=project_score, reverse=True)
    skill_contributors: Dict[str, List[Contributor]] = {}
    for contributor in contributors:
        for skill in contributor.skills.values():
            if skill.name not in skill_contributors:
                skill_contributors[skill.name] = [contributor]
            else:
                skill_contributors[skill.name].append(contributor)
    for skill, people in skill_contributors.items():
        people.sort(key=lambda x: x.skills[skill].level)
    curr_time = 0
    result: List[Tuple[Project, List[Contributor]]] = []
    for project in projects:
        if curr_time + project.days_to_complete >= project.best_before + project.score:
            continue
        selected: List[Contributor] = []
        sel_set: Set[str] = set()
        skip_project: bool = False
        for role in project.roles:
            possible_people = skill_contributors[role.name]
            min_skill_index = bin_search(possible_people, role.level, role.name)
            if min_skill_index >= len(possible_people) or min_skill_index < 0:
                skip_project = True
                break
            min_time_person = None
            min_time_free = 10000000000000
            for i in range(min_skill_index, len(possible_people)):
                person = possible_people[min_skill_index]
                if person.name in sel_set:
                    continue
                if person.available_at <= curr_time:
                    min_time_free = curr_time
                    min_time_person = person
                    break
                if person.available_at <= min_time_free:
                    min_time_free = person.available_at
                    min_time_person = person
            if min_time_person is None:
                skip_project = True
                break
            if min_time_free + project.days_to_complete >= project.best_before + project.score:
                skip_project = True
                break
            curr_time = min_time_free
            selected.append(min_time_person)
            sel_set.add(min_time_person.name)
        if skip_project:
            continue
        for person in selected:
            person.available_at = curr_time + project.days_to_complete
        result.append((project, selected))
    return result


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
        ('inputs/b_better_start_small.in.txt', 'outputs/b_better_start_small.out.txt'),
        ('inputs/c_collaboration.in.txt', 'outputs/c_collaboration.out.txt'),
        ('inputs/d_dense_schedule.in.txt', 'outputs/d_dense_schedule.out.txt'),
        ('inputs/e_exceptional_skills.in.txt', 'outputs/e_exceptional_skills.out.txt'),
        ('inputs/f_find_great_mentors.in.txt', 'outputs/f_find_great_mentors.out.txt')
    ]
    for in_file, out_file in test_cases:
        run(in_file, out_file)
