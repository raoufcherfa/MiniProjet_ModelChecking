CFLAGS= -I lib/
PROJECTNAME= mainModelChecking.cpp

all: classes
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking ./obj/expressionAnalyseur.o ./obj/etatMachine.o ./obj/appelerOperation.o -Wall

classes:
	@mkdir -p obj bin
	@g++ -c ./src/expressionAnalyseur.cpp $(CFLAGS) -o ./obj/expressionAnalyseur.o -Wall
	@g++ -c ./src/etatMachine.cpp $(CFLAGS) -o ./obj/etatMachine.o -Wall
	@g++ -c ./src/appelerOperation.cpp $(CFLAGS) -o ./obj/appelerOperation.o -Wall

clean:
	@rm -rf bin obj
	@find -name "*~" | xargs rm -rf

run: ./bin/modelchecking
	./bin/modelchecking < ${IN}
