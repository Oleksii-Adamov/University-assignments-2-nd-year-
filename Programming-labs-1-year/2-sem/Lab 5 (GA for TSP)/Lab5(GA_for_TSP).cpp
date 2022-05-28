// Вирішити задачу комівояжера за допомогою генетичного алгоритму.
#include<iostream>
#include<algorithm>
#include<ctime>
#include<fstream>
using namespace std;
const int NUMBER_OF_CITIES = 51;
const int NUMBER_OF_INDIVIDUALS = 500;
const int MUTATION_RATE = 200; // possibility = MUTATION_RATE/32767
const int NUMBER_OF_GENERATIONS = 1000;
const int NUMBER_OF_ELITES = 2;
const int CORRECT_ANS = 675; // 51 - 426 - best accur = 98%, 76 - 538 - accur = 88%, 70 - 675 - accur = 94.5%
const double EPS = 1e-1;
int cur_mutation_rate = MUTATION_RATE;
struct City { // or Gene
	double x, y;
	int num;
};
struct Individual { // or Route
	double fitness;
	int route_length;
	City route[NUMBER_OF_CITIES]; // chromosome
};
int nint(double x) {
	return (int)(x + 0.5);
}
int distance(City a, City b) {
	double delta_x = a.x - b.x;
	double delta_y = a.y - b.y;
	return nint(sqrt(delta_x * delta_x + delta_y * delta_y));
}
int calc_route_length(Individual a) {
	int route_length = 0;
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		if (i + 1 != NUMBER_OF_CITIES) {
			route_length += distance(a.route[i], a.route[i + 1]);
		}
		else {
			route_length += distance(a.route[i], a.route[0]);
		}
	}
	return route_length;
}
double get_route_length(Individual& a) {
	if (abs(a.route_length - (-1)) < EPS) a.route_length = calc_route_length(a);
	return a.route_length;
}
double calc_fitness(Individual a) {
	return 1 / ((double) get_route_length(a));
}
double get_fitness(Individual &a) {
	if (abs(a.fitness - (-1)) < EPS) a.fitness = calc_fitness(a);
	return a.fitness;
}
bool comp_individ(Individual x, Individual y) {
	return get_fitness(x) > get_fitness(y);
}
bool is_valid(Individual a) {
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		if (a.route[i].num < 0) return false;
	}
	return true;
}
Individual* mating_pool(Individual population[NUMBER_OF_INDIVIDUALS], int size) {
	Individual* pool = new Individual[size];
	// Tournament selection
	for (int i = 0; i < size; i++) {
		int index1 = rand() % NUMBER_OF_INDIVIDUALS;
		int index2 = rand() % NUMBER_OF_INDIVIDUALS;
		if (get_fitness(population[index1]) > get_fitness(population[index2])) {
			pool[i] = population[index1];
		}
		else 
			pool[i] = population[index2];
	}
	return pool;
}
bool city_cmp(City a, City b) {
	return a.num < b.num;
}
pair<Individual, Individual> breed(Individual a, Individual b) {
	Individual first_child;
	first_child.fitness = -1;
	first_child.route_length = -1;
	Individual second_child;
	second_child.fitness = -1;
	second_child.route_length = -1;
	int geneA = rand() % NUMBER_OF_CITIES, geneB = rand() % NUMBER_OF_CITIES;
	int start_gene = min(geneA, geneB), end_gene = max(geneA, geneB), sub_route_size = end_gene - start_gene + 1;
	City* a_sub_route = new City[sub_route_size];
	City* b_sub_route = new City[sub_route_size];
	for (int i = start_gene; i <= end_gene; i++) {
		int ind = i - start_gene;
		a_sub_route[ind] = a.route[i];
		b_sub_route[ind] = b.route[i];
		first_child.route[i] = a.route[i];
		second_child.route[i] = b.route[i];
	}
	sort(a_sub_route, a_sub_route + sub_route_size, city_cmp);
	sort(b_sub_route, b_sub_route + sub_route_size, city_cmp);
	int ind_f = 0, ind_s = 0;
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		if (!binary_search(a_sub_route, a_sub_route + sub_route_size, b.route[i], city_cmp)) {
			if (ind_f == start_gene) ind_f = end_gene + 1;
			if (ind_f < NUMBER_OF_CITIES) {
				first_child.route[ind_f] = b.route[i];
				ind_f++;
			}
		}
		if (!binary_search(b_sub_route, b_sub_route + sub_route_size, a.route[i], city_cmp)) {
			if (ind_s == start_gene) ind_s = end_gene + 1;
			if (ind_s < NUMBER_OF_CITIES) {
				second_child.route[ind_s] = a.route[i];
				ind_s++;
			}
		}
	}
	delete[] a_sub_route;
	delete[] b_sub_route;
	return { first_child, second_child };
}
void swap_cities(City& a, City& b) {
	City t = a;
	a = b;
	b = t;
}
void mutate(Individual &a) {
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		if (rand() < cur_mutation_rate) {
			int j = rand() % NUMBER_OF_CITIES;
			swap_cities(a.route[i], a.route[j]);
		}
	}
}
void next_generation(Individual population[NUMBER_OF_INDIVIDUALS]) {
	int m_pool_size = NUMBER_OF_INDIVIDUALS - NUMBER_OF_ELITES;
	Individual* m_pool = mating_pool(population, m_pool_size);
	sort(m_pool, m_pool + m_pool_size, comp_individ);
	for (int i = 0; i < NUMBER_OF_ELITES; i++) {
		population[i] = m_pool[i];
		mutate(population[i]); // ?
	}
	int ind = NUMBER_OF_ELITES;
	for (int i = 0; ind < NUMBER_OF_INDIVIDUALS; i+=2) {
		if (i + 1 == m_pool_size) {
			population[ind] = m_pool[i];
			break;
		}
		pair<Individual, Individual> children = breed(m_pool[i], m_pool[i + 1]);
		population[ind] = children.first;
		mutate(population[ind]);
		ind++;
		if (ind < NUMBER_OF_INDIVIDUALS) {
			population[ind] = children.second;
			mutate(population[ind]);
			ind++;
		}
	}
	delete[] m_pool;
}
void copy(const City from[NUMBER_OF_CITIES], City to[NUMBER_OF_CITIES]) {
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		to[i] = from[i];
	}
}
void init_population(Individual population[NUMBER_OF_INDIVIDUALS], City cities[NUMBER_OF_CITIES]) {
	for (int i = 0; i < NUMBER_OF_INDIVIDUALS; i++) {
		population[i].fitness = -1;
		population[i].route_length = -1;
		random_shuffle(cities, cities + NUMBER_OF_CITIES);
		copy(cities, population[i].route);
	}
}
Individual genetic_algo(const City input[NUMBER_OF_CITIES]) {
	Individual prev_best;
	prev_best.route_length = -2;
	City input_copy[NUMBER_OF_CITIES];
	copy(input, input_copy);
	Individual* population = new Individual[NUMBER_OF_INDIVIDUALS];
	init_population(population, input_copy);
	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
		next_generation(population);
		int best = 0;
		for (int i = 1; i < NUMBER_OF_INDIVIDUALS; i++) {
			if (get_fitness(population[i]) > get_fitness(population[best])) {
				best = i;
			}
		}
		if (get_route_length(prev_best) == -2 || get_route_length(population[best]) < get_route_length(prev_best)) {
			prev_best = population[best];
		}
		cout << get_route_length(population[best]) << "\n";
	}
	delete[] population;
	return prev_best;
}
int main() {
	srand(time(0));
	ifstream cin("input51.txt");
	City input[NUMBER_OF_CITIES];
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		cin >> input[i].num >> input[i].x >> input[i].y;
	}
	Individual solution = genetic_algo(input);
	cout << "min_length = " << get_route_length(solution) << "\nAccuracy: " 
		<< (1 - ((double) (get_route_length(solution) - CORRECT_ANS)) / CORRECT_ANS)*100 << "%\n";
	cout << "Route\n";
	for (int i = 0; i < NUMBER_OF_CITIES; i++) {
		cout << solution.route[i].num << " -> ";
	}
	cout << solution.route[0].num << "\n";
}
