CXX = g++
DEMO_INC = -I$(ROOT_DIR)/include -I$(ROOT_DIR) -I/usr/include -I/usr/local/include
DEMO_LIBS = -lbrsdk -lz -lpthread -ldl -lrt -lssl -lcrypto 
DEMO_LIB_PATH = -L$(ROOT_DIR)/build -L$(ROOT_DIR)/lib -L/usr/local/lib
FLASGS = -Wall -std=c++11 -g -D__const__= -pipe -W -Wall -Wno-unused-parameter \
			-fPIC -fno-omit-frame-pointer -Wno-implicit-fallthrough \
			-fstack-protector-all -Wno-deprecated-declarations \
			-Wno-class-memaccess \
			-Wno-unused-result -Wno-maybe-uninitialized
DEMOS =  demo_net demo_net_echo demo_atomic demo_co demo_crypto demo_ds demo_time demo_process

all: $(DEMOS)
	@echo "BUILD DEMO SUCCESS."

demo_atomic:
	@echo "$(CXX) demo_atomic.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_atomic.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_co:
	@echo "$(CXX) demo_co.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_co.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_crypto:
	@echo "$(CXX) demo_crypto.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_crypto.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_ds:
	@echo "$(CXX) demo_ds.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_ds.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_net:
	@echo "$(CXX) demo_net.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_net.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_net_echo:
	@echo "$(CXX) demo_net_echo.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_net_echo.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_time:
	@echo "$(CXX) demo_time.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_time.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

demo_process:
	@echo "$(CXX) demo_process.cpp -o $(OUTPUT_DIR)/$@"
	@$(CXX) demo_process.cpp -o $(OUTPUT_DIR)/$@ $(DEMO_INC) $(DEMO_LIBS) $(DEMO_LIB_PATH) $(FLASGS)

