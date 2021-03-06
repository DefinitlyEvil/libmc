/*
 * Copyright (c) 2016 Jonathan Glines
 * Jonathan Glines <jonathan@glines.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <assert.h>

#define MC_CUBE_HAVE_TABLES
#include <mc/algorithms/common/cube.h>

#include "canonical_cube_orientations.h"

#include "cube_tables.c"

/* NOTE: This is a little bit awkward, but it is difficult to export the
 * generated list of orientations as an enum type. */
const unsigned int mcCube_canonicalOrientations[] = {
  MC_CUBE_CANONICAL_ORIENTATION_0,
  MC_CUBE_CANONICAL_ORIENTATION_1,
  MC_CUBE_CANONICAL_ORIENTATION_2,
  MC_CUBE_CANONICAL_ORIENTATION_3,
  MC_CUBE_CANONICAL_ORIENTATION_4,
  MC_CUBE_CANONICAL_ORIENTATION_5,
  MC_CUBE_CANONICAL_ORIENTATION_6,
  MC_CUBE_CANONICAL_ORIENTATION_7,
  MC_CUBE_CANONICAL_ORIENTATION_8,
  MC_CUBE_CANONICAL_ORIENTATION_9,
  MC_CUBE_CANONICAL_ORIENTATION_10,
  MC_CUBE_CANONICAL_ORIENTATION_11,
  MC_CUBE_CANONICAL_ORIENTATION_12,
  MC_CUBE_CANONICAL_ORIENTATION_13,
  MC_CUBE_CANONICAL_ORIENTATION_14,
  MC_CUBE_CANONICAL_ORIENTATION_15,
  MC_CUBE_CANONICAL_ORIENTATION_16,
  MC_CUBE_CANONICAL_ORIENTATION_17,
  MC_CUBE_CANONICAL_ORIENTATION_18,
  MC_CUBE_CANONICAL_ORIENTATION_19,
  MC_CUBE_CANONICAL_ORIENTATION_20,
  MC_CUBE_CANONICAL_ORIENTATION_21,
  MC_CUBE_CANONICAL_ORIENTATION_22,
};

/* NOTE: This is a little bit awkward, but it is difficult to export the
 * generated list of orientations as an enum type. */
const unsigned int mcCube_canonicalOrientationInversions[] = {
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_0,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_1,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_2,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_3,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_4,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_5,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_6,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_7,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_8,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_9,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_10,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_11,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_12,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_13,
  MC_CUBE_CANONICAL_ORIENTATION_INVERSION_14,
};

void mcCube_edgeSampleIndices(unsigned int edge, unsigned int *sampleIndices) {
  typedef struct SampleIndexPair {
    int sampleIndices[2];
  } SampleIndexPair;
  static const SampleIndexPair table[] = {
    { .sampleIndices = { 0, 1 } },  /* Edge 0 */
    { .sampleIndices = { 1, 5 } },  /* Edge 1 */
    { .sampleIndices = { 4, 5 } },  /* Edge 2 */
    { .sampleIndices = { 0, 4 } },  /* Edge 3 */
    { .sampleIndices = { 2, 3 } },  /* Edge 4 */
    { .sampleIndices = { 3, 7 } },  /* Edge 5 */
    { .sampleIndices = { 6, 7 } },  /* Edge 6 */
    { .sampleIndices = { 2, 6 } },  /* Edge 7 */
    { .sampleIndices = { 0, 2 } },  /* Edge 8 */
    { .sampleIndices = { 1, 3 } },  /* Edge 9 */
    { .sampleIndices = { 4, 6 } },  /* Edge 10 */
    { .sampleIndices = { 5, 7 } },  /* Edge 11 */
  };
  assert(edge < 12);
  sampleIndices[0] = table[edge].sampleIndices[0];
  sampleIndices[1] = table[edge].sampleIndices[1];
}

void mcCube_edgeFaces(unsigned int edge, unsigned int *faces) {
  typedef struct FacePair {
    int faces[2];
  } FacePair;
  /* FIXME: The face pair table no longer suggests the correct winding order
   * now that the sample indices have been changed. */
  static const FacePair table[] = {
    { .faces = { 0, 3 } },  /* Edge 0 */
    { .faces = { 0, 1 } },  /* Edge 1 */
    { .faces = { 0, 2 } },  /* Edge 2 */
    { .faces = { 4, 0 } },  /* Edge 3 */
    { .faces = { 3, 5 } },  /* Edge 4 */
    { .faces = { 1, 5 } },  /* Edge 5 */
    { .faces = { 2, 5 } },  /* Edge 6 */
    { .faces = { 5, 4 } },  /* Edge 7 */
    { .faces = { 3, 4 } },  /* Edge 8 */
    { .faces = { 1, 3 } },  /* Edge 9 */
    { .faces = { 4, 2 } },  /* Edge 10 */
    { .faces = { 2, 1 } },  /* Edge 11 */
  };
  assert (edge < 12);
  faces[0] = table[edge].faces[0];
  faces[1] = table[edge].faces[1];
}

int mcCube_sampleIndicesToEdge(unsigned int a, unsigned int b) {
  assert(a >= 0);
  assert(a < 8);
  assert(b >= 0);
  assert(b < 8);
  switch (a) {
    case 0:
      switch (b) {
        case 1:
          return 0;
        case 2:
          return 8;
        case 4:
          return 3;
      }
      break;
    case 1:
      switch (b) {
        case 0:
          return 0;
        case 3:
          return 9;
        case 5:
          return 1;
      }
      break;
    case 2:
      switch (b) {
        case 0:
          return 8;
        case 3:
          return 4;
        case 6:
          return 7;
      }
      break;
    case 3:
      switch (b) {
        case 1:
          return 9;
        case 2:
          return 4;
        case 7:
          return 5;
      }
      break;
    case 4:
      switch (b) {
        case 0:
          return 3;
        case 5:
          return 2;
        case 6:
          return 10;
      }
      break;
    case 5:
      switch (b) {
        case 1:
          return 1;
        case 4:
          return 2;
        case 7:
          return 11;
      }
      break;
    case 6:
      switch (b) {
        case 2:
          return 7;
        case 4:
          return 10;
        case 7:
          return 6;
      }
      break;
    case 7:
      switch (b) {
        case 3:
          return 5;
        case 5:
          return 11;
        case 6:
          return 6;
      }
      break;
  }
  return -1;
}

void mcCube_sampleEdges(unsigned int sampleIndex, int *edges) {
  typedef struct EdgeTriple {
    int edges[3];
  } EdgeTriple;
  static const EdgeTriple table[] = {
    { .edges = {  0,  3,  8 } },  /* Sample 0 */
    { .edges = {  0,  1,  9 } },  /* Sample 1 */
    { .edges = {  4,  7,  8 } },  /* Sample 2 */
    { .edges = {  4,  5,  9 } },  /* Sample 3 */
    { .edges = {  2,  3, 10 } },  /* Sample 4 */
    { .edges = {  1,  2, 11 } },  /* Sample 5 */
    { .edges = {  6,  7, 10 } },  /* Sample 6 */
    { .edges = {  5,  6, 11 } },  /* Sample 7 */
  };
  assert(sampleIndex < 8);
  edges[0] = table[sampleIndex].edges[0];
  edges[1] = table[sampleIndex].edges[1];
  edges[2] = table[sampleIndex].edges[2];
}

void mcCube_adjacentSamples(unsigned int sampleIndex, unsigned int *adjacent) {
  typedef struct SampleIndexTriple {
    int sampleIndices[3];
  } VertexTriple;
  static const VertexTriple table[] = {
    { .sampleIndices = { 1, 2, 4 } },  /* Sample 0 */
    { .sampleIndices = { 0, 3, 5 } },  /* Sample 1 */
    { .sampleIndices = { 0, 3, 6 } },  /* Sample 2 */
    { .sampleIndices = { 1, 2, 7 } },  /* Sample 3 */
    { .sampleIndices = { 0, 5, 6 } },  /* Sample 4 */
    { .sampleIndices = { 1, 4, 7 } },  /* Sample 5 */
    { .sampleIndices = { 2, 4, 7 } },  /* Sample 6 */
    { .sampleIndices = { 3, 5, 6 } },  /* Sample 7 */
  };
  assert(sampleIndex < 8);
  adjacent[0] = table[sampleIndex].sampleIndices[0];
  adjacent[1] = table[sampleIndex].sampleIndices[1];
  adjacent[2] = table[sampleIndex].sampleIndices[2];
}

int mcCube_sampleValue(unsigned int sampleIndex, unsigned int cube) {
  return (cube & (1 << sampleIndex)) >> sampleIndex;
}

unsigned int mcCube_sampleIndex(unsigned int x, unsigned int y, unsigned int z) {
  assert((x & ~1) == 0);
  assert((y & ~1) == 0);
  assert((z & ~1) == 0);
  unsigned int result = 0;
  result |= x ? 1 << 0 : 0;
  result |= y ? 1 << 1 : 0;
  result |= z ? 1 << 2 : 0;
  return result;
}

void mcCube_vertexClosure(unsigned int vertex, unsigned int cube,
    unsigned int *closure, unsigned int *closureSize)
{
  unsigned int notVisited[8];
  unsigned int numNotVisited;
  unsigned int visited[8];
  unsigned int numVisited;
  unsigned int adjacent[3];
  int skip;
  int i, j;
  int vertexValue = mcCube_sampleValue(vertex, cube);

  notVisited[0] = vertex;
  numNotVisited = 1;

  numVisited = 0;

  *closureSize = 0;

  /* Visit all vertices we have not yet visited */
  while (numNotVisited > 0) {
    /* Pop a vertex not yet visited from the stack */
    numNotVisited -= 1;
    /* Add this vertex to the list of visited vertices */
    visited[numVisited++] = notVisited[numNotVisited];
    /* Add this vertex to the closure */
    closure[(*closureSize)++] = notVisited[numNotVisited];
    /* Iterate over all adjacent vertices */
    mcCube_adjacentSamples(notVisited[numNotVisited], adjacent);
    for (i = 0; i < 3; ++i) {
      /* Check if this vertex has already been visited */
      skip = 0;
      for (j = 0; j < numVisited; ++j) {
        if (adjacent[i] == visited[j]) {
          skip = 1;
          break;
        }
      }
      if (skip)
        continue;
      /* Add alike vertices to the list of not yet visited vertices */
      if (mcCube_sampleValue(adjacent[i], cube) == vertexValue)
        notVisited[numNotVisited++] = adjacent[i];
    }
  }
}

void mcCube_boundryEdges(unsigned int vertex, unsigned int cube,
    unsigned int *edges, unsigned int *numEdges)
{
  unsigned int notVisited[8];
  unsigned int numNotVisited;
  unsigned int current;
  unsigned int visited[8];
  unsigned int numVisited;
  unsigned int adjacent[3];
  int skip;
  int i, j;
  int vertexValue = mcCube_sampleValue(vertex, cube);

  notVisited[0] = vertex;
  numNotVisited = 1;

  numVisited = 0;

  *numEdges = 0;

  /* Visit all vertices we have not yet visited */
  while (numNotVisited > 0) {
    /* Pop a vertex not yet visited from the stack */
    numNotVisited -= 1;
    current = notVisited[numNotVisited];
    /* Add this vertex to the list of visited vertices */
    visited[numVisited++] = current;
    /* Iterate over all adjacent vertices */
    mcCube_adjacentSamples(current, adjacent);
    for (i = 0; i < 3; ++i) {
      /* Check if this vertex has already been visited */
      skip = 0;
      for (j = 0; j < numVisited; ++j) {
        if (adjacent[i] == visited[j]) {
          skip = 1;
          break;
        }
      }
      if (skip)
        continue;
      if (mcCube_sampleValue(adjacent[i], cube) == vertexValue) {
        /* Add alike vertices to the list of not yet visited vertices */
        notVisited[numNotVisited++] = adjacent[i];
      } else {
        /* Add boundry edges to the list of edges */
        edges[(*numEdges)++] = mcCube_sampleIndicesToEdge(current, adjacent[i]);
      }
    }
  }
}

void mcCube_sampleRelativePosition(unsigned int sampleIndex, unsigned int *pos) {
  pos[0] = (sampleIndex & (1 << 0)) >> 0;
  pos[1] = (sampleIndex & (1 << 1)) >> 1;
  pos[2] = (sampleIndex & (1 << 2)) >> 2;
}

unsigned int mcCube_cubeConfigurationFromSamples(float *samples) {
  unsigned int cube = 0;
  for (unsigned int vertex = 0; vertex < 8; ++vertex) {
    /* Add the bit this vertex contributes to the cube */
    cube |= (samples[vertex] >= 0.0f ? 1 : 0) << vertex;
  }
  assert(cube <= 0xff);
  return cube;
}

unsigned int mcCube_canonicalOrientation(unsigned int cube) {
  assert(cube <= 0xff);
  return mcCube_canonicalOrientationTable[cube];
}

unsigned int mcCube_canonicalRotationSequence(unsigned int cube) {
  assert(cube <= 0xff);
  return mcCube_canonicalRotationSequenceTable[cube];
}

unsigned int mcCube_canonicalOrientationInversion(unsigned int cube) {
  assert(cube <= 0xff);
  return mcCube_canonicalOrientationInversionTable[cube];
}

unsigned int mcCube_canonicalRotationInversionSequence(unsigned int cube) {
  assert(cube <= 0xff);
  return mcCube_canonicalRotationInversionSequenceTable[cube];
}

int mcCube_rotateCubeX(int cube) {
  assert(cube >= 0);
  assert(cube <= 0xff);
  return mcCube_rotationTableX[cube];
}

int mcCube_rotateCubeY(int cube) {
  assert(cube >= 0);
  assert(cube <= 0xff);
  return mcCube_rotationTableY[cube];
}

int mcCube_rotateCubeZ(int cube) {
  assert(cube >= 0);
  assert(cube <= 0xff);
  return mcCube_rotationTableZ[cube];
}

unsigned int mcCube_rotateEdgeX(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeRotationTableX[edge];
}

unsigned int mcCube_rotateEdgeY(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeRotationTableY[edge];
}

unsigned int mcCube_rotateEdgeZ(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeRotationTableZ[edge];
}

unsigned int mcCube_rotateEdgeReverseX(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeReverseRotationTableX[edge];
}

unsigned int mcCube_rotateEdgeReverseY(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeReverseRotationTableY[edge];
}

unsigned int mcCube_rotateEdgeReverseZ(unsigned int edge) {
  assert(edge < MC_CUBE_NUM_EDGES);
  return mcCube_edgeReverseRotationTableZ[edge];
}

unsigned int mcCube_translateEdge(unsigned int edge, unsigned int face) {
  assert(edge < MC_CUBE_NUM_EDGES);
  assert(face < MC_CUBE_NUM_FACES);
  return mcCube_edgeTranslationTable[(face << 4) + edge];
}

int mcCube_getCubeFace(int cube, int faceIndex) {
  int result = 0;
#define FACE_BIT(in, out) \
  result |= (cube & (1 << (in))) ? (1 << (out)) : 0;
#define FACE_BITS(a, b, c, d) \
  do { \
    FACE_BIT(a, 0) \
    FACE_BIT(b, 1) \
    FACE_BIT(c, 2) \
    FACE_BIT(d, 3) \
  } while (0)
  switch (faceIndex) {
    case 0:
      /* The front face */
      FACE_BITS(0, 1, 5, 4);
      break;
    case 1:
      /* The left face */
      FACE_BITS(1, 3, 7, 5);
      break;
    case 2:
      /* The top face */
      FACE_BITS(4, 5, 7, 6);
      break;
    case 3:
      /* The bottom face */
      FACE_BITS(0, 2, 3, 1);
      break;
    case 4:
      /* The right face */
      FACE_BITS(0, 4, 6, 2);
      break;
    case 5:
      /* The back face */
      FACE_BITS(2, 6, 7, 3);
      break;
  }
  return result;
}

int mcCube_isAmbiguousFace(int face) {
  assert(face >= 0);
  assert(face <= 0xf);
  switch (face) {
    case 0x5:
    case 0xa:
      return 1;
  }
  return 0;
}

int mcCube_hasAmbiguousFace(int cube) {
  /* Check all faces of the cube for the ambiguous cases */
  for (int faceIndex = 0; faceIndex < 6; ++faceIndex) {
    int face = mcCube_getCubeFace(cube, faceIndex);
    if (mcCube_isAmbiguousFace(face)) {
      return 1;
    }
  }
  return 0;
}
