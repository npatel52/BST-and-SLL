#include<iostream>
#include<string>
#include "sll.h"

SLL<char> sll;

bool test_length(std::string str){
  int result = sll.length();
  int expected = str.length();
  bool pass = (expected == result);
  std::cout<< (pass ? "PASSED " : "FAILED ") << " Expected: " << expected << " length( )=> " << result << std::endl;
  return pass;
}

template <typename E> bool test_contains(std::string str, E const value){
  bool result = sll.contains(value);
  bool expected = (str.find(value) != std::string::npos);
  bool  pass = (expected == result);
  std::cout<< (  pass? "PASSED " : "FAILED ") << " Expected: " << expected << " contains ( " << value << " ) => " << result << std::endl;
  return pass;
}

template <typename E> bool test_item_at(std::string str, unsigned int const pos){
  bool pass = true;
  try{
     E result = sll.item_at(pos);
     char expected = str.at(pos);
     pass = (expected == result);
     std::cout<< ( pass ?  "PASSED " : "FAILED " ) << " Expected: " << expected << " item_at_( " << pos << " ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
     std::cout<< e.what() <<std::endl;
  }
  return pass;
}

template <typename E> bool test_item_at_head(std::string str){
  bool pass = true;
  try{
     E result = sll.item_at_head();
     char expected = str.at(0);
     pass = (expected == result);
     std::cout<< ( pass?  "PASSED " : "FAILED " ) << " Expected: " << expected << " item_at_head( ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
     std::cout<< e.what() <<std::endl;
  }
  return true;
}

template <typename E> bool test_item_at_tail(std::string str){
  bool pass = true;
  try{
     E result = sll.item_at_tail();
     char expected = str.at(str.length()-1);
     pass = (expected == result);
     std::cout<< ( pass ?  "PASSED " : "FAILED " ) << " Expected: " << expected << " item_at_tail( ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
     std::cout<< e.what() <<std::endl;
  }
  return pass;
}


template <typename E> bool test_decapitate(std::string str){
   bool pass = true;
  try{
     E result = sll.decapitate();
     char expected = str.at(0);
     pass = (expected == result); 
     std::cout<< ( pass ?  "PASSED " : "FAILED " ) << " Expected: " << expected << " decapitate( ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
     std::cout<< e.what() <<std::endl;
  }
  return pass;
}


template <typename E> bool test_decaudate(std::string str){
   bool pass = true;
  try{
     E result = sll.decaudate();
     char expected = str.at(str.length() - 1);
     pass = (expected == result); 
     std::cout<< ( pass ?  "PASSED " : "FAILED " ) << " Expected: " << expected << " decapitate( ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
     std::cout<< e.what() <<std::endl;
  }
  return pass;
}

template <typename E> bool test_remove_at(std::string str, unsigned int const pos){
  bool pass = true;
  try{
     E result = sll.remove_at(pos);
     char expected = str.at(pos);
     pass = (expected == result);
     std::cout<< ( pass ?  "PASSED " : "FAILED " ) << " Expected: " << expected << " remove_at( " << pos << " ) => " << result << std::endl;
  }catch(const std::runtime_error& e){
    std::cout<< "Pos: " << pos << " is not a valid position to remove." <<std::endl;
  }
  return pass;
} 


bool  test_removeDuplicates(std::string str){
  sll.removeDuplicates();
  std::string result = sll.to_string();
  bool  pass = str.compare(result) == 0;
  std::cout<< ( pass ? "PASSED " : "FAILED " ) << " Expected : " << str << " Result : " << result << std::endl;
  return pass;
}
int main(){

  sll.append('l');
  sll.append('i');
  sll.append('n');
  sll.append('k');
  sll.append('e');
  sll.append('d');
  sll.prepend('l');;
  sll.prepend('l');
  sll.prepend('s');;
  
  std::string s = sll.to_string();

  bool test_passed = true;

  test_passed = test_passed && test_length(s);
  test_passed = test_passed && test_contains<char>(s,'s');
  test_passed = test_passed && test_contains<char>(s,'-');
  test_passed = test_passed && test_item_at<char>(s,0);
  test_passed = test_passed && test_item_at<char>(s,8);
  test_passed = test_passed && test_item_at_head<char>(s);
  test_passed = test_passed && test_item_at_tail<char>(s);
  // Update string
  s = sll.to_string();

  // Test remove duplicates
  std::string nonDuplicate = "slinked";
  test_passed = test_passed && test_removeDuplicates(nonDuplicate);

  // Update string
  s = sll.to_string();
  
  test_passed = test_passed && test_remove_at<char>(s,0);

  s = sll.to_string();
  test_passed = test_passed && test_remove_at<char>(s,5);

  s = sll.to_string();
  test_passed = test_passed && test_remove_at<char>(s,1);

  s = sll.to_string();
  test_passed = test_passed && test_remove_at<char>(s,3);

  s = sll.to_string();
  test_passed = test_passed && test_decapitate<char>(s);
  test_passed = test_passed && test_decaudate<char> (s);
  
  std::cout<< (test_passed ? "SUCCESS! " : "FAILURE!") <<std::endl;

  sll.print();
  
  sll.~SLL();
  return 0;
}
