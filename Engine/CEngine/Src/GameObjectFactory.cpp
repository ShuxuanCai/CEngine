#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ColiderComponent.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "FPSCameraControllerComponent.h"
#include "AnimatorComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsComponent.h"

using namespace CEngine;

namespace rj = rapidjson;

namespace
{
    CustomMake TryMake;
}

void GameObjectFactory::SetCustomMake(CustomMake customMake)
{
    TryMake = customMake;
}

void GameObjectFactory::Make(const std::filesystem::path& templateFile, GameObject& gameObject)
{
    static float shiftX = 0.0f;

    FILE* file = nullptr;
    auto err = fopen_s(&file, templateFile.u8string().c_str(), "r");
    ASSERT(err == 0 && file != nullptr, "GameObjectFactory -- failed to open template file %s", templateFile.u8string().c_str());

    char readBuffer[65536];
    rj::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));

    fclose(file);

    rj::Document doc;
    doc.ParseStream(readStream);

    auto components = doc["Components"].GetObj();
    for (auto& component : components)
    {
        const char* componentName = component.name.GetString();
        if (TryMake(componentName, component.value, gameObject))
        {
            
        }
        else if (strcmp(componentName, "AnimatorComponent") == 0)
        {
            auto animatorComponent = gameObject.AddComponent<AnimatorComponent>();
        }
        else if (strcmp(componentName, "CameraComponent") == 0)
        {
            auto cameraComponent = gameObject.AddComponent<CameraComponent>();
            if (component.value.HasMember("Position"))
            {
                const auto& center = component.value["Position"].GetArray();
                const float x = center[0].GetFloat();
                const float y = center[1].GetFloat();
                const float z = center[2].GetFloat();
                cameraComponent->GetCamera().SetPosition({ x, y, z });
            }
            if (component.value.HasMember("LookAt"))
            {
                const auto& center = component.value["LookAt"].GetArray();
                const float x = center[0].GetFloat();
                const float y = center[1].GetFloat();
                const float z = center[2].GetFloat();
                cameraComponent->GetCamera().SetLookAt({ x, y, z });
            }
            if (component.value.HasMember("FOV"))
            {
                const float fov = component.value["FOV"].GetFloat();
                cameraComponent->GetCamera().SetFov(fov);
            }
            if (component.value.HasMember("AspectRatio"))
            {
                const float aspectRatio = component.value["AspectRatio"].GetFloat();
                cameraComponent->GetCamera().SetAspectRatio(aspectRatio);
            }
            if (component.value.HasMember("NearPlane"))
            {
                const float nearPlane = component.value["NearPlane"].GetFloat();
                cameraComponent->GetCamera().SetNearPlane(nearPlane);
            }
            if (component.value.HasMember("FarPlane"))
            {
                const float farPlane = component.value["FarPlane"].GetFloat();
                cameraComponent->GetCamera().SetFarPlane(farPlane);
            }
        }
        else if (strcmp(componentName, "ColiderComponent") == 0)
        {
            auto colliderComponent = gameObject.AddComponent<ColiderComponent>();
            if (component.value.HasMember("Extents"))
            {
                const auto& extents = component.value["Extents"].GetArray();
                const float x = extents[0].GetFloat();
                const float y = extents[1].GetFloat();
                const float z = extents[2].GetFloat();
                colliderComponent->SetExtend({ x, y, z });
            }
            if (component.value.HasMember("Origin"))
            {
                const auto& origin = component.value["Origin"].GetArray();
                const float x = origin[0].GetFloat();
                const float y = origin[1].GetFloat();
                const float z = origin[2].GetFloat();
                colliderComponent->SetOrigin({ x, y, z });
            }
        }
        else if (strcmp(componentName, "FPSCameraControllerComponent") == 0)
        {
            auto fpsCameraController = gameObject.AddComponent<FPSCameraControllerComponent>();
            if (component.value.HasMember("MoveSpeed"))
            {
                const float moveSpeed = component.value["MoveSpeed"].GetFloat();
                fpsCameraController->SetMoveSpeed(moveSpeed);
            }
            if (component.value.HasMember("TurnSpeed"))
            {
                const float turnSpeed = component.value["TurnSpeed"].GetFloat();
                fpsCameraController->SetTurnSpeed(turnSpeed);
            }
        }
        else if (strcmp(componentName, "ModelComponent") == 0)
        {
            auto modelComponent = gameObject.AddComponent<ModelComponent>();
            if (component.value.HasMember("FileName"))
            {
                const char* fileName = component.value["FileName"].GetString();
                modelComponent->SetFileName(fileName);
            }
            if (component.value.HasMember("Animations"))
            {
                const auto& animationNames = component.value["Animations"].GetArray();
                for (const auto& animationName : animationNames)
                {
                    const char* animation = animationName.GetString();
                    modelComponent->AddAnimation(animation);
                }
            }
        }
        else if (strcmp(componentName, "MeshComponent") == 0)
        {
            auto meshComponent = gameObject.AddComponent<MeshComponent>();
            if (component.value.HasMember("Shape"))
            {
                std::string shape = component.value["Shape"].GetString();
                if (shape == "Cube")
                {
                    float size = component.value["Size"].GetFloat();
                    meshComponent->CreateCube(size);
                }
                else if (shape == "Sphere")
                {
                    int slices = component.value["Slices"].GetInt();
                    int rings = component.value["Rings"].GetInt();
                    float radius = component.value["Radius"].GetFloat();
                    meshComponent->CreateSphere(slices, rings, radius);
                }
                else if (shape == "Plane")
                {
                    int columns = component.value["Columns"].GetInt();
                    int rows = component.value["Rows"].GetInt();
                    float spacing = component.value["Spacing"].GetFloat();
                    meshComponent->CreatePlane(columns, rows, spacing);
                }
                else
                {
                    ASSERT(false, "Shape type not available.");
                }
            }
            if (component.value.HasMember("Material"))
            {
                const auto& materialData = component.value["Material"];
                if (materialData.HasMember("Ambient"))
                {
                    const auto& color = materialData["Ambient"].GetArray();
                    const float r = color[0].GetFloat();
                    const float g = color[1].GetFloat();
                    const float b = color[2].GetFloat();
                    meshComponent->SetAmbientColor({ r, g, b, 1.0f });
                }
                if (materialData.HasMember("Diffuse"))
                {
                    const auto& color = materialData["Diffuse"].GetArray();
                    const float r = color[0].GetFloat();
                    const float g = color[1].GetFloat();
                    const float b = color[2].GetFloat();
                    meshComponent->SetDiffuseColor({ r, g, b, 1.0f });
                }
                if (materialData.HasMember("Specular"))
                {
                    const auto& color = materialData["Specular"].GetArray();
                    const float r = color[0].GetFloat();
                    const float g = color[1].GetFloat();
                    const float b = color[2].GetFloat();
                    meshComponent->SetSpecularColor({ r, g, b, 1.0f });
                }
                if (materialData.HasMember("SpecularPower"))
                {
                    const float power = materialData["SpecularPower"].GetFloat();
                    meshComponent->SetSpecularPower(power);
                }
            }
            if (component.value.HasMember("Textures"))
            {
                const auto& textureData = component.value["Textures"];
                if (textureData.HasMember("DiffuseMap"))
                {
                    const char* fileName = textureData["DiffuseMap"].GetString();
                    meshComponent->SetDiffuseMap(fileName);
                }
                if (textureData.HasMember("BumpMap"))
                {
                    const char* fileName = textureData["BumpMap"].GetString();
                    meshComponent->SetBumpMap(fileName);
                }
                if (textureData.HasMember("NormalMap"))
                {
                    const char* fileName = textureData["NormalMap"].GetString();
                    meshComponent->SetNormalMap(fileName);
                }
                if (textureData.HasMember("SpecularMap"))
                {
                    const char* fileName = textureData["SpecularMap"].GetString();
                    meshComponent->SetSpecularMap(fileName);
                }
            }
        }
        else if (strcmp(componentName, "RigidBodyComponent") == 0)
        {
            auto rigidBodyComponent = gameObject.AddComponent<RigidBodyComponent>();
            auto physicsComponent = gameObject.AddComponent<PhysicsComponent>();
            if (component.value.HasMember("Mass"))
            {
                const float mass = component.value["Mass"].GetFloat();
                rigidBodyComponent->SetMass(mass);
            }
        }
        else if (strcmp(componentName, "TransformComponent") == 0)
        {
            auto transformComponent = gameObject.AddComponent<TransformComponent>();
            if (component.value.HasMember("Position"))
            {
                const auto& pos = component.value["Position"].GetArray();
                const float x = pos[0].GetFloat() + shiftX;
                const float y = pos[1].GetFloat();
                const float z = pos[2].GetFloat();
                transformComponent->position = { x, y, z };

                shiftX += 2.0f;
            }
            if (component.value.HasMember("Rotation"))
            {
                const auto& rot = component.value["Rotation"].GetArray();
                const float x = rot[0].GetFloat();
                const float y = rot[1].GetFloat();
                const float z = rot[2].GetFloat();
                const float w = (rot.Size() > 3) ? rot[3].GetFloat() : 1.0f;
                transformComponent->rotation = { x, y, z, w };
            }
            if (component.value.HasMember("Scale"))
            {
                const auto& scale = component.value["Scale"].GetArray();
                float x, y, z;
                if (scale.Size() > 1)
                {
                    x = scale[0].GetFloat();
                    y = scale[1].GetFloat();
                    z = scale[2].GetFloat();
                }
                else
                {
                    x = scale[0].GetFloat();
                    y = scale[0].GetFloat();
                    z = scale[0].GetFloat();
                }
                transformComponent->scale = { x, y, z };
            }
        }
        else
        {
            ASSERT(false, "ObjectFactory -- %s was not defined", componentName);
        }
        // add more components
    }

    //static float x = 0.0f;

    //if (templateFile == "Camera")
    //{
    //    CameraComponent* cameraComponent = gameObject.AddComponent<CameraComponent>();
    //    cameraComponent->GetCamera().SetPosition({ 0.0f, 3.0f, -5.0f });
    //    cameraComponent->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });

    //    FPSCameraControllerComponent* fpsCameraControllerComponent = gameObject.AddComponent< FPSCameraControllerComponent>();
    //    //fpsCameraControllerComponent->SetSpeed(); // SetTurnSpeed
    //}
    //else
    //{
    //    // this is where we would 
    //    TransformComponent* transform = gameObject.AddComponent<TransformComponent>();
    //    transform->position = { x, 0.0, 3.0f };

    //    ColiderComponent* collider = gameObject.AddComponent<ColiderComponent>();
    //    collider->SetCenter({ 0.0f, 0.5f, 0.0f });
    //    collider->SetExtend({ 0.5f, 0.5f, 0.5f });

    //    ModelComponent* modelComponent = gameObject.AddComponent<ModelComponent>();
    //    modelComponent->SetFileName("../../Assets/Models/Character/Ch35_nonPBR.model");
    //    modelComponent->AddAnimation("../../Assets/Models/Character/rifle_aiming_idle.model");
    //    gameObject.AddComponent<AnimatorComponent>();

    //    x += 2.0f;
    //}
}