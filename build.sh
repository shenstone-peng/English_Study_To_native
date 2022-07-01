g++ -c quiz.cpp ./lib_json/json_reader.cpp ./lib_json/json_writer.cpp ./lib_json/json_value.cpp -I ./
g++ -g main.cpp -I ./ -o out quiz.o json_reader.o json_writer.o json_value.o
