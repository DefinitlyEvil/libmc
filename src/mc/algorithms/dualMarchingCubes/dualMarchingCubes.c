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

#include <mc/algorithms/common/dual.h>
#include <mc/algorithms/patch.h>

void mcDualMarchingCubes_isosurfaceFromField(
    mcScalarFieldWithArgs sf, const void *args,
    unsigned int x_res, unsigned int y_res, unsigned int z_res,
    const mcVec3 *min, const mcVec3 *max,
    mcMesh *mesh)
{
  mcMesh cubesMesh;
  mcMesh *dualMesh = mesh;

  mcMesh_init(&cubesMesh);
  mcPatch_isosurfaceFromField(
      sf, args,
      x_res, y_res, z_res,
      min, max,
      &cubesMesh);

  /* The maximum number of adjacent faces in a marching cubes mesh is four. See
   * Nielson for details. */
  mcDual_makeDual(
      &cubesMesh,  /* mesh */
      4,  /* maxFacesPerVertex */
      dualMesh  /* dual */
      );

  mcMesh_destroy(&cubesMesh);
}
