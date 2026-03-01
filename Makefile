all:
	make run
clean:
	rm build/*
run:
	go run cmd/client/client.go
test:
	make test_alg
	make test_graph
test_graph:
	go test ./pkg/graph/
test_alg:
	go test ./pkg/algorithms/
