#include <cmath>
#include <exception>

#include "3dviewer.h"
#include "gtest/gtest.h"

TEST(TestReadScene, Test1) {
  s21::Facade facade;
  facade.renderTheScene("models/cube.obj");

  size_t expectedCountVertices = 24;
  EXPECT_EQ(facade.getCountVertices() * 3, expectedCountVertices);

  float *vertices = facade.getVertices();
  float expectedVertices[] = {1.,  1.,  -1., 1., -1., -1., 1.,  1.,
                              1.,  1.,  -1., 1., -1., 1.,  -1., -1.,
                              -1., -1., -1., 1., 1.,  -1., -1., 1.};

  for (size_t i = 0; i < expectedCountVertices; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]);
  }

  size_t expectedCountFaces = 6;
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);

  unsigned int *indicesInFace = facade.getIndicesInFace();
  unsigned int expectedIndicesInFace[] = {4, 4, 4, 4, 4, 4};

  for (size_t i = 0; i < expectedCountFaces; ++i) {
    EXPECT_EQ(indicesInFace[i], expectedIndicesInFace[i]) << "i=" << i;
  }

  size_t expectedCountIndices = 24;
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  unsigned int *indices = facade.getIndices();
  unsigned int expectedIndices[] = {1, 5, 7, 3, 4, 3, 7, 8, 8, 7, 5, 6,
                                    6, 2, 4, 8, 2, 1, 3, 4, 6, 5, 1, 2};

  for (size_t i = 0; i < expectedCountIndices; ++i) {
    EXPECT_EQ(indices[i], expectedIndices[i]);
  }

  size_t expectedCountEdges = 12;
  EXPECT_EQ(facade.getCountEdges(), expectedCountEdges);

  unsigned int *edges = facade.getEdges();
  unsigned int expectedEdges[] = {1, 2, 1, 3, 1, 5, 2, 4, 2, 6, 3, 4,
                                  3, 7, 4, 8, 5, 6, 5, 7, 6, 8, 7, 8};
  for (size_t i = 0; i < expectedCountEdges * 2; ++i) {
    EXPECT_EQ(edges[i], expectedEdges[i]) << i;
  }

  s21::NormalizationParameters parameters = facade.getParameters();
  s21::NormalizationParameters expectedParameters{};
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(parameters.min[i], expectedParameters.min[i]);
    EXPECT_EQ(parameters.max[i], expectedParameters.max[i]);
  }
}

TEST(TestReadScene, Test2) {
  s21::Facade facade("models/cat.obj");

  size_t expectedCountVertices = 3408;
  EXPECT_EQ(facade.getCountVertices() * 3, expectedCountVertices);

  float *vertices = facade.getVertices();
  float expectedVertices[] = {
      -122.049975, 177.452652, -71.317341, 259.629959, 236.275313, -7.978126,
      -135.291002, 27.678053,  -41.460398, 248.049564, 283.428948, -23.379235,
      213.59685,   217.595912, -5.356867,  189.907774, 315.746688, -9.763807,
      213.683303,  320.086776, -59.122126, 213.045692, 287.030148, -51.465066};

  for (size_t i = 0; i < 24; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]);
  }

  size_t expectedCountFaces = 2082;
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);

  unsigned int *indicesInFace = facade.getIndicesInFace();
  unsigned int expectedIndicesInFace[] = {3, 3, 3, 3, 3, 3, 3, 3,
                                          3, 3, 3, 3, 3, 3, 3};

  for (size_t i = 0; i < 15; ++i) {
    EXPECT_EQ(indicesInFace[i], expectedIndicesInFace[i]) << "i=" << i;
  }

  size_t expectedCountIndices = 6246;
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  unsigned int *indices = facade.getIndices();
  unsigned int expectedIndices[] = {322, 247, 323, 245, 323, 247, 247, 246,
                                    245, 244, 245, 246, 245, 244, 238, 244,
                                    246, 243, 235, 238, 244, 244, 243, 235};

  for (size_t i = 0; i < 24; ++i) {
    EXPECT_EQ(indices[i], expectedIndices[i]) << i;
  }
}

TEST(TestMoveSceneCubeX, Test1) {
  s21::Facade facade("models/cube.obj");

  float expectedVertices[24] = {
      2.000000, 1.000000, -1.000000, 2.000000, -1.000000, -1.000000,
      2.000000, 1.000000, 1.000000,  2.000000, -1.000000, 1.000000,
      0.000000, 1.000000, -1.000000, 0.000000, -1.000000, -1.000000,
      0.000000, 1.000000, 1.000000,  0.000000, -1.000000, 1.000000};

  facade.moveScene(1., 0., 0.);

  size_t expectedCountVertices = 8;
  size_t expectedCountFaces = 6;
  size_t expectedCountIndices = 24;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < expectedCountVertices * 3; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]) << i;
  }
}

TEST(TestMoveSceneCatX, Test1) {
  s21::Facade facade("models/cat.obj");

  float expectedVertices[24] = {
      -121.049975, 177.452652, -71.317341, 260.629959, 236.275313, -7.978126,
      -134.291002, 27.678053,  -41.460398, 249.049564, 283.428948, -23.379235,
      214.59685,   217.595912, -5.356867,  190.907774, 315.746688, -9.763807,
      214.683303,  320.086776, -59.122126, 214.045692, 287.030148, -51.465066};

  facade.moveScene(1., 0., 0.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]) << i;
  }
}

TEST(TestMoveSceneCatY, Test1) {
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {
      -122.049975, 178.452652, -71.317341, 259.629959, 237.275313, -7.978126,
      -135.291002, 28.678053,  -41.460398, 248.049564, 284.428948, -23.379235,
      213.59685,   218.595912, -5.356867,  189.907774, 316.746688, -9.763807,
      213.683303,  321.086776, -59.122126, 213.045692, 288.030148, -51.465066};

  facade.moveScene(0., 1., 0.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]) << i;
  }
}

TEST(TestMoveSceneCatZ, Test1) {
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {
      -122.049975, 177.452652, -70.317341, 259.629959, 236.275313, -6.978126,
      -135.291002, 27.678053,  -40.460398, 248.049564, 283.428948, -22.379235,
      213.59685,   217.595912, -4.356867,  189.907774, 315.746688, -8.763807,
      213.683303,  320.086776, -58.122126, 213.045692, 287.030148, -50.465066};

  facade.moveScene(0., 0., 1.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]) << i;
  }
}

TEST(TestScaleSceneCube, Test1) {
  s21::Facade facade("models/cube.obj");

  float expectedVertices[24] = {
      0.1000000,  0.1000000, -0.1000000, 0.1000000,  -0.1000000, -0.1000000,
      0.1000000,  0.1000000, 0.1000000,  0.1000000,  -0.1000000, 0.1000000,
      -0.1000000, 0.1000000, -0.1000000, -0.1000000, -0.1000000, -0.1000000,
      -0.1000000, 0.1000000, 0.1000000,  -0.1000000, -0.1000000, 0.1000000};

  facade.scaleScene(0.1);

  size_t expectedCountVertices = 8;
  size_t expectedCountFaces = 6;
  size_t expectedCountIndices = 24;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < expectedCountVertices * 3; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]) << i;
  }
}

TEST(TestScaleSceneCat, Test1) {
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {
      -12.205,  17.7453, -7.13173,  25.963,  23.6275, -0.797813,
      -13.5291, 2.76781, -4.14604,  24.805,  28.3429, -2.33792,
      21.3597,  21.7596, -0.535687, 18.9908, 31.5747, -0.976381,
      21.3683,  32.0087, -5.91221,  21.3046, 28.703,  -5.14651};

  facade.scaleScene(0.1);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], 0.0001) << i;
  }
}

TEST(TestXRotateSceneCube, Test1) {
  const float epsilon = 1e-6;
  s21::Facade facade("models/cube.obj");

  float expectedVertices[24] = {
      1.000000,  1.000000, -1.000000, 1.000000,  -1.000000, -1.000000,
      1.000000,  1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,
      -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000,
      -1.000000, 1.000000, 1.000000,  -1.000000, -1.000000, 1.000000};

  facade.xRotateScene(360.);

  size_t expectedCountVertices = 8;
  size_t expectedCountFaces = 6;
  size_t expectedCountIndices = 24;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < expectedCountVertices * 3; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestXRotateSceneCat, Test1) {
  const float epsilon = 1e-3;
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {
      -122.049975, 177.452652, -71.317341, 259.629959, 236.275313, -7.978126,
      -135.291002, 27.678053,  -41.460398, 248.049564, 283.428948, -23.379235,
      213.59685,   217.595912, -5.356867,  189.907774, 315.746688, -9.763807,
      213.683303,  320.086776, -59.122126, 213.045692, 287.030148, -51.465066};

  facade.xRotateScene(360.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestYRotateSceneCube, Test1) {
  const float epsilon = 1e-6;
  s21::Facade facade("models/cube.obj");

  float expectedVertices[24] = {
      -1.000000, 1.000000, 1.000000,  -1.000000, -1.000000, 1.000000,
      -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000,
      1.000000,  1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,
      1.000000,  1.000000, -1.000000, 1.000000,  -1.000000, -1.000000};

  facade.yRotateScene(180.);

  size_t expectedCountVertices = 8;
  size_t expectedCountFaces = 6;
  size_t expectedCountIndices = 24;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < expectedCountVertices * 3; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestYRotateSceneCat, Test1) {
  const float epsilon = 1e-3;
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {
      122.049975,  177.452652, 71.317341, -259.629959, 236.275313, 7.978126,
      135.291002,  27.678053,  41.460398, -248.049564, 283.428948, 23.379235,
      -213.59685,  217.595912, 5.356867,  -189.907774, 315.746688, 9.763807,
      -213.683303, 320.086776, 59.122126, -213.045692, 287.030148, 51.465066};

  facade.yRotateScene(180.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestZRotateSceneCube, Test1) {
  const float epsilon = 1e-6;
  s21::Facade facade("models/cube.obj");

  float expectedVertices[24] = {
      -1.000000, 1.000000,  -1.000000, 1.000000, 1.000000,  -1.000000,
      -1.000000, 1.000000,  1.000000,  1.000000, 1.000000,  1.000000,
      -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000,
      -1.000000, -1.000000, 1.000000,  1.000000, -1.000000, 1.000000};

  facade.zRotateScene(90.);

  size_t expectedCountVertices = 8;
  size_t expectedCountFaces = 6;
  size_t expectedCountIndices = 24;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < expectedCountVertices * 3; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestZRotateSceneCat, Test1) {
  const float epsilon = 1e-3;
  s21::Facade facade("models/cat.obj");

  float expectedVertices[] = {-177.453, -122.05,  -71.3173, -236.275, 259.63,
                              -7.97813, -27.6781, -135.291, -41.4604, -283.429,
                              248.05,   -23.3792, -217.596, 213.597,  -5.35687,
                              -315.747, 189.908,  -9.76381, -320.087, 213.683,
                              -59.1221, -287.03,  213.046,  -51.4651};

  facade.zRotateScene(90.);

  size_t expectedCountVertices = 1136;
  size_t expectedCountFaces = 2082;
  size_t expectedCountIndices = 6246;

  EXPECT_EQ(facade.getCountVertices(), expectedCountVertices);
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  float *vertices = facade.getVertices();
  for (size_t i = 0; i < 24; ++i) {
    EXPECT_NEAR(vertices[i], expectedVertices[i], epsilon) << i;
  }
}

TEST(TestEqualPoints, Test1) {
  s21::Point3d firstPoint(-122.049975, 177.452652, -71.317341);
  s21::Point3d secondPoint(-122.049975, 177.452652, -71.317341);
  EXPECT_TRUE(firstPoint == secondPoint);
}

TEST(TestEqualPoints1, Test1) {
  s21::Point3d firstPoint(-1342.049975, 157.452652, -731.317341);
  s21::Point3d secondPoint(-1243.049975, 177.452652, -71.317341);
  EXPECT_FALSE(firstPoint == secondPoint);
}

TEST(CreateNewPoint, Test1) {
  s21::Point3d firstPoint(-122.049975, 157.452652, -71.317341);
  float expectedVertices[] = {-1243.049975, 177.452652, -71.317341};
  firstPoint.setCoordinates(-1243.049975, 177.452652, -71.317341);
  EXPECT_EQ(firstPoint.x, expectedVertices[0]);
  EXPECT_EQ(firstPoint.y, expectedVertices[1]);
  EXPECT_EQ(firstPoint.z, expectedVertices[2]);
}

TEST(VertexEqual, Test1) {
  s21::Point3d firstPoint(259.689121, 289.238756, 15.728211);
  s21::Point3d secondPoint(259.689121, 289.238756, 15.728211);
  s21::Vertex firstVertex(firstPoint);
  s21::Vertex secondVertex(secondPoint);
  EXPECT_TRUE(firstVertex == secondVertex);
}

TEST(VertexEqual1, Test1) {
  s21::Point3d firstPoint(259.689121, 289.238756, 15.728211);
  s21::Point3d secondPoint(259.689121, 2849.238756, 135.728211);
  s21::Vertex firstVertex(firstPoint);
  s21::Vertex secondVertex(secondPoint);
  EXPECT_FALSE(firstVertex == secondVertex);
}

TEST(FaceEquals, Test1) {
  std::vector<unsigned int> a1 = {23, 43, 54, 76, 56, 23, 12, 54};
  std::vector<unsigned int> a2 = {23, 43, 54, 76, 56, 23, 12, 54};
  s21::Face firstFace(a1);
  s21::Face secondFace(a2);
  EXPECT_TRUE(firstFace == secondFace);
}

TEST(FaceEquals1, Test1) {
  std::vector<unsigned int> a1 = {2333, 4123, 54, 76, 5346, 2323, 1332, 5434};
  std::vector<unsigned int> a2 = {2233, 43, 54, 7346, 56, 23, 1223, 54};
  s21::Face firstFace(a1);
  s21::Face secondFace(a2);
  EXPECT_FALSE(firstFace == secondFace);
}

TEST(TestNormalization, Test1) {
  s21::Facade facade("models/cube.obj", true);

  size_t expectedCountVertices = 24;
  EXPECT_EQ(facade.getCountVertices() * 3, expectedCountVertices);

  float *vertices = facade.getVertices();
  float expectedVertices[] = {
      0.500000,  0.500000, -0.500000, 0.500000,  -0.500000, -0.500000,
      0.500000,  0.500000, 0.500000,  0.500000,  -0.500000, 0.500000,
      -0.500000, 0.500000, -0.500000, -0.500000, -0.500000, -0.500000,
      -0.500000, 0.500000, 0.500000,  -0.500000, -0.500000, 0.5000000};

  for (size_t i = 0; i < expectedCountVertices; ++i) {
    EXPECT_EQ(vertices[i], expectedVertices[i]);
  }

  size_t expectedCountFaces = 6;
  EXPECT_EQ(facade.getCountFaces(), expectedCountFaces);

  unsigned int *indicesInFace = facade.getIndicesInFace();
  unsigned int expectedIndicesInFace[] = {4, 4, 4, 4, 4, 4};

  for (size_t i = 0; i < expectedCountFaces; ++i) {
    EXPECT_EQ(indicesInFace[i], expectedIndicesInFace[i]) << "i=" << i;
  }

  size_t expectedCountIndices = 24;
  EXPECT_EQ(facade.getCountIndices(), expectedCountIndices);

  unsigned int *indices = facade.getIndices();
  unsigned int expectedIndices[] = {1, 5, 7, 3, 4, 3, 7, 8, 8, 7, 5, 6,
                                    6, 2, 4, 8, 2, 1, 3, 4, 6, 5, 1, 2};

  for (size_t i = 0; i < expectedCountIndices; ++i) {
    EXPECT_EQ(indices[i], expectedIndices[i]);
  }

  size_t expectedCountEdges = 12;
  EXPECT_EQ(facade.getCountEdges(), expectedCountEdges);

  unsigned int *edges = facade.getEdges();
  unsigned int expectedEdges[] = {1, 2, 1, 3, 1, 5, 2, 4, 2, 6, 3, 4,
                                  3, 7, 4, 8, 5, 6, 5, 7, 6, 8, 7, 8};
  for (size_t i = 0; i < expectedCountEdges * 2; ++i) {
    EXPECT_EQ(edges[i], expectedEdges[i]);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
