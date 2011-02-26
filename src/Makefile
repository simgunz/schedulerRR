Job.o:
	$(CXX) -c job.cpp

Task.o:
	$(CXX) -c task.cpp

PeriodicTask.o:
	$(CXX) -c periodictask.cpp

Processor.o:
	$(CXX) -c processor.cpp

SchedulerRR.o:
	$(CXX) -c schedulerRR.cpp

SchedulerRR:SchedulerRR.o Processor.o PeriodicTask.o Task.o Job.o
	$(CXX) -o ../schedulerRR main.cpp schedulerRR.o processor.o periodictask.o task.o job.o

all: SchedulerRR

clean:
	rm *.o
