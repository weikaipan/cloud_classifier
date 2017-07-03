TARGET=cloud kmeans hac create_data individual_create pdf
GPP=g++
BIN=../bin
INCLUDE=-I../include
FLAG=-g
VERSION=-std=c++0x
OPT=-O2
WARNING=-Wall
CONFIG=../config/variables
OUTPUT=../one_file_test/output.txt
PNAME=../data/raw_data/flag/2013

PDF_OBJS=pdf.o
CLOUD_OBJS=cloud.o
CREATE_DATA_OBJS=create_data.o
KMEANS_OBJS=kmeans.o
HAC_OBJS=hac.o

.PHONY: clean all
all: $(TARGET)

%.o: %.cpp
	@echo "making: " $@
	@$(GPP) $< -c $(FLAG) $(VERSION) $(OPT) $(WARNING) $(INCLUDE)

clean:
	rm -rf *.o
	@for bin in $(TARGET); do \
		echo "rm -rf $(BIN)/$$bin"; \
		rm -rf $(BIN)/$$bin; \
	done
pdf: $(PDF_OBJS)
	@echo "making: " $@
	@$(GPP) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(VERSION) $(OPT) $(WARNING) $(PDF_OBJS)
	
create_data: $(CREATE_DATA_OBJS)
	@echo "making: " $@
	@$(GPP) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(VERSION) $(OPT) $(WARNING) $(CREATE_DATA_OBJS)

kmeans: $(KMEANS_OBJS)
	@echo "making: " $@
	@$(GPP) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(VERSION) $(OPT) $(WARNING) $(KMEANS_OBJS)


hac: $(HAC_OBJS)
	@echo "making: " $@	
	@$(GPP) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(VERSION) $(OPT) $(WARNING) $(HAC_OBJS)

cloud: $(CLOUD_OBJS)
	@echo "making: " $@
	@$(GPP) -o $(BIN)/$@ $(FLAG) $(INCLUDE) $(VERSION) $(OPT) $(WARNING) $(CLOUD_OBJS)

run:
	@for i in $$PNAME; do \
		@echo "processing : $$i."; \
		$(BIN)/create_data $(CONFIG) $(OUTPUT) $$i;\
	done	
