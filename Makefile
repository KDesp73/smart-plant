.DEFAULT_GOAL := help

.PHONY: build
build: cc ## Compile
	pio run

.PHONY: upload
upload: cc ## Upload the script
	pio run -t upload

.PHONY: monitor
monitor: ## Start monitoring the port
	pio device monitor

.PHONY: cc
cc: ## Export compile commands
	pio run -t compiledb

.PHONY: clean
clean: ## Clean project
	pio run -t clean

.PHONY: help
help: ## Show this help message
	@echo "Available commands:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

