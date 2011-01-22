Job.o:
	$(CXX) -c job.cpp

Task.o:
	$(CXX) -c task.cpp

Processor.o:
	$(CXX) -c processor.cpp

SchedulerRR.o:
	$(CXX) -c schedulerRR.cpp

SchedulerTest:SchedulerRR.o Processor.o Task.o Job.o
	$(CXX) -o ../schedulerTest schedulerTest.cpp schedulerRR.o processor.o task.o job.o

all: SchedulerTest

clean:
	rm *.o
