Job.o:
	$(CXX) -c job.cpp

Processor.o:
	$(CXX) -c processor.cpp

SchedulerRR.o:
	$(CXX) -c schedulerRR.cpp

SchedulerTest:SchedulerRR.o Processor.o Job.o
	$(CXX) -o ../schedulerTest schedulerTest.cpp schedulerRR.o job.o

all: SchedulerTest

clean:
	rm *.o
