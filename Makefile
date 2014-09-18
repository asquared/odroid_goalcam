all: goalcam

goalcam_OBJS = \
	main.o \
	mfc_decoder.o

goalcam: $(goalcam_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $<
