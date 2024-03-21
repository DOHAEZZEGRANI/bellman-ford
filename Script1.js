// JavaScript source code
const fs = require('fs');

class Graph {
  constructor() {
    this.vertices = new Map();
  }

  addVertex(vertex) {
    if (!this.vertices.has(vertex)) {
      this.vertices.set(vertex, []);
    }
  }

  addEdge(source, destination, weight) {
    this.addVertex(source);
    this.addVertex(destination);
    this.vertices.get(source).push({ destination, weight });
  }

  printGraph() {
    for (const [vertex, edges] of this.vertices.entries()) {
      const edgeString = edges.map(edge => `${edge.destination}(${edge.weight})`).join(', ');
      console.log(`Vertex ${vertex}: ${edgeString}`);
    }
  }
}

function readGraphFromFile(filename) {
  const data = fs.readFileSync(filename, 'utf-8');
  const lines = data.trim().split('\n');

  const numVertices = parseInt(lines[0], 10);
  const graph = new Graph();

  for (let i = 1; i < lines.length; i++) {
    const [source, destination, weight] = lines[i].split(' ').map(Number);
    graph.addEdge(source, destination, weight);
  }

  return { numVertices, graph };
}

function main() {
  const { numVertices, graph } = readGraphFromFile('dohaa.txt');
  console.log('Number of Vertices:', numVertices);
  console.log('Graph:');
  graph.printGraph();
}

main();
