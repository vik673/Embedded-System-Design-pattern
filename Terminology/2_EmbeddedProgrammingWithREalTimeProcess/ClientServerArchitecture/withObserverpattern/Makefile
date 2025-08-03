# Makefile for Observer Pattern Implementation

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc
TARGET = observer_pattern_demo
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Dependencies (simplified - in practice you'd use automatic dependency generation)
$(SRCDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/TestBuilder.h $(SRCDIR)/ECG_Module.h
$(SRCDIR)/TestBuilder.o: $(SRCDIR)/TestBuilder.c $(SRCDIR)/TestBuilder.h $(SRCDIR)/ECGPkg.h
$(SRCDIR)/TMDQueue.o: $(SRCDIR)/TMDQueue.c $(SRCDIR)/TMDQueue.h $(SRCDIR)/NotificationHandle.h
$(SRCDIR)/NotificationHandle.o: $(SRCDIR)/NotificationHandle.c $(SRCDIR)/NotificationHandle.h
$(SRCDIR)/TimeMarkedData.o: $(SRCDIR)/TimeMarkedData.c $(SRCDIR)/TimeMarkedData.h
$(SRCDIR)/ECG_Module.o: $(SRCDIR)/ECG_Module.c $(SRCDIR)/ECG_Module.h
$(SRCDIR)/HistogramDisplay.o: $(SRCDIR)/HistogramDisplay.c $(SRCDIR)/HistogramDisplay.h
$(SRCDIR)/WaveformDisplay.o: $(SRCDIR)/WaveformDisplay.c $(SRCDIR)/WaveformDisplay.h
$(SRCDIR)/QRSDetector.o: $(SRCDIR)/QRSDetector.c $(SRCDIR)/QRSDetector.h
$(SRCDIR)/ArrythmiaDetector.o: $(SRCDIR)/ArrythmiaDetector.c $(SRCDIR)/ArrythmiaDetector.h
