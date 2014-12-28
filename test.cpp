/*
 Example how too use my library "Naive Bayers Text Classifier" 
 Author: Cooler_
 Contact: c00f3r[at]gmail[dot]com

*/
#include "libtext_bayes.h"
#include <iostream>

int main(int argc, char* argv[])
{
  NaiveBayes robot;

  robot.set_training_data_file(std::string("training_quotes3.txt"));

  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");
  robot.add_training_data("compre agora promoção SPAM");
  robot.add_training_data("preço super barato SPAM");
  robot.add_training_data("aproveite agora somente nesta sexta SPAM");
  robot.add_training_data("ola meu amigo como vai você ? OK");
  robot.add_training_data("pagamento efetuado OK");
  robot.add_training_data("esta tudo certo velho amigo OK");

  robot.train();

  std::string class_ = robot.classify(std::string("agora aproveite e compre"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("ola meu amigo como vai as coisas ?"));
  std::cout << "High CLASS is " << class_ << std::endl;

  class_ = robot.classify(std::string("videos porno apenas por 200 super barato"));
  std::cout << "High CLASS is " << class_ << std::endl;
 
  robot.free_bayers(); 

  return 0;
}
