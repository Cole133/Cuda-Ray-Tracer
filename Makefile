.PHONY: all compile run clean

BUILD_DIR  := build
OUTPUT_DIR := output
BIN        := $(BUILD_DIR)/CudaRayTracing

all: run

compile:
	@[ -d $(BUILD_DIR) ] || cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

run: compile
	@mkdir -p $(OUTPUT_DIR)
	@N=$$(ls $(OUTPUT_DIR)/render*.ppm 2>/dev/null \
	    | sed -n 's|.*/render\([0-9]\{1,\}\)\.ppm$$|\1|p' \
	    | sort -n | tail -n1); \
	 N=$${N:-3}; \
	 NEXT=$$((N + 1)); \
	 if [ $$NEXT -lt 4 ]; then NEXT=4; fi; \
	 OUT=$(OUTPUT_DIR)/render$$NEXT.ppm; \
	 PNG=$${OUT%.ppm}.png; \
	 echo "Rendering to $$OUT"; \
	 $(BIN) > $$OUT \
	   && ffmpeg -y -loglevel error -i $$OUT $$PNG \
	   && echo "Converted to $$PNG" \
	   && xdg-open $$PNG

clean:
	rm -rf $(BUILD_DIR)
