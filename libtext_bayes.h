/*
#    Copyright (C) 2014 libtext_bayes authors(Antonio Costa, Cooler_),
#    
#    This file is part of libtext_bayers
#    
#    libtext_bayes is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    libtext_bayes is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _H_LIBTEXT_BAYES
#define _H_LIBTEXT_BAYES

#include <map>
#include <string>
#include <vector>
/*
In machine learning, naive Bayes classifiers are a family of simple probabilistic classifiers 
based on applying Bayes' theorem with strong (naive) independence assumptions between the features.

Naive Bayes models are also known under a variety of names in the literature, including simple
Bayes and independence Bayes.[1] All these names  reference the use of Bayes' theorem in the 
classifier's decision rule, but naive Bayes is not (necessarily) a Bayesian method;[1] Russell 
and Norvig  note that "[naive Bayes] is sometimes called a Bayesian classifier, a somewhat 
careless usage that has prompted true Bayesians to call it the idiot Bayes model.

P(Ci|X) = P(X|Ci)P(Ci) / P(X)

A naive bayes classifier returns a class (C = Ci) for which P(Ci|X) is maximum.

Since P(X) is constant for all classes we maximize only the numerator P(X|Ci)P(Ci) 
to obtain the highest probability for a class (P(Ci|X)).

P(X|Ci) = PRODUCT P(Xk|Ci) for k from 1 to n = P(x1|Ci) * P(x2|Ci) * ... * P(xn|Ci)
The above assumes class conditional independence.

P(Xi|Ci) = Count(Xi AND Ci) / Count(Ci)

*/
typedef std::map<std::string, double> MapSD;
typedef std::map<std::string, int> MapSI;
typedef std::map<std::string, MapSD*> MapOfMaps;
typedef std::vector<std::string> StringVector;
typedef std::vector<StringVector> DualVector;

const char DELIM = ' ';

class NaiveBayes
{
public:
	NaiveBayes() {}
	~NaiveBayes() {}
	void train();
	void free_bayers();
	void set_training_data_file(std::string filepath);
	void get_training_data();
	void add_training_data(std::string data);
	std::string classify(const std::string& input_attr);

private:
	double get_prob_for_class(const StringVector& attr, const std::string& class_label);
	int total_unique_class_attr_pairs;
	int total_unique_attr_count; 
	std::string training_data_filepath;
	DualVector attributes; 
	StringVector classes; 
	MapSD class_probs; 
	MapSD class_counts; 
	MapSI unique_class_attr_counts; 
	MapOfMaps class_attr_event;
	MapOfMaps class_attr_pair_counts;
};

#endif 
