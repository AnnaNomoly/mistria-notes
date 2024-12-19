# Scripts

### Ari Scripts
These scripts involve the Ari object `{obj_ari}`.
- [gml_Script_modify_health@Ari@Ari](#gml_script_modify_healthariari)

## gml_Script_modify_health@Ari@Ari
#### Description
Modifies Ari's health (HP) by the specified amount.

#### Variables
| Variable         | Kind                          | Value          | Notes |
|------------------|-------------------------------|----------------|--------------------------------------------------------------|
| `Self`           | `CInstance*`                  | `{obj_ari}`    | A pointer to the `CInstance` for the `obj_ari` game object.  |
| `Other`          | `CInstance*`                  | `???`          | Needs additional research.                                   |
| `ArgumentCount`  | `int`                         | `1`            | The number of inbound arguments.                             |
| `Arguments[0]`   | `RValueType::VALUE_REAL`      | `<double>`     | Health modifier, may be positive or negative, including 0.   |
| `Result`         | `RValueType::VALUE_UNDEFINED` |                | Not used.                                                    |

#### Example Use
In this example, the `gml_Script_modify_health@Ari@Ari` script is called inside `ObjectCallback` when the target `self` is named `obj_ari` and a boolean `recover` is true, to increase Ari's HP by `10`.
```cpp
void ObjectCallback(
    IN FWCodeEvent& CodeEvent
)
{
    auto& [self, other, code, argc, argv] = CodeEvent.Arguments();
    
    if (!self)
        return;
    
    if (!self->m_Object)
        return;
    
    if (strstr(self->m_Object->m_Name, "obj_ari"))
    {
        if(recover)
        {
            CScript* gml_script_modify_health = nullptr;
            g_ModuleInterface->GetNamedRoutinePointer(
                "gml_Script_modify_health@Ari@Ari",
                (PVOID*)&gml_script_modify_health
            );

            CInstance* global_instance = nullptr;
            g_ModuleInterface->GetGlobalInstance(&global_instance);

            RValue result;
            RValue argument = 10.0;
            RValue* argument_ptr = &argument;
            
            gml_script_modify_health->m_Functions->m_ScriptFunction(
                global_instance->at("__ari").m_Object,
                self,
                result,
                1,
                { &argument_ptr }
            );
        }
    }
}

```
