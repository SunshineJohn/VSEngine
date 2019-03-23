#include "Scene.h"
#include "Components/SceneObject.h"

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

namespace VSEngine
{
Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::LoadScene(GLuint program_)
{
  program = program_;
  for (SceneObject *object : sceneObjects)
  {
    object->BindObject(program);
  }

  lightColor = glGetUniformLocation(program, "lightColor");
  lightPosition = glGetUniformLocation(program, "lightPosition");

  viewMatrix = glGetUniformLocation(program, "viewMatrix");
}

void Scene::RenderScene(double time)
{
  glUseProgram(program);

  glUniform3f(lightColor, 1.0f, 0.0f, 0.0f);
  glUniform3f(lightPosition, 100.0f, 100.0f, 100.0f);

  static double prevTime = 0;
  float delta = static_cast<float>(time - prevTime);
  camera.SetSpeed(delta * 20.0f);
  prevTime = time;

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

  for (SceneObject *object : sceneObjects)
  {
    object->Render(time);
  }
}

void Scene::AddSceneObject(SceneObject *object)
{
  sceneObjects.push_back(object);
}

void Scene::SetCamera(const Camera &cam)
{
  camera = cam;
}

void Scene::MoveCamera(MoveDirection direction)
{
  camera.MoveCamera(direction);
}

void Scene::RotateCamera(float deltaYaw, float deltaPitch)
{
  camera.RotateCamera(deltaYaw, deltaPitch);
}

}
