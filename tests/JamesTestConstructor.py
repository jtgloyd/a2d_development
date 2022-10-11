import types
from typing import List, Dict, Callable, Any, Set, Tuple
import numpy


# class TestFunction:
#     name: str
#
#     @property
#     def body(self):
#         return f"""\
#     // Declarations and Initializations:
#     ...
#     // Evaluations:
#     ...
#     // Comparisons:
#     ...
#     // End Test\
# """
#
#     pass
#
#
# class TestClass:
#     name: str
#     test_functions: List[TestFunction]
#
#     def _test_f_(self, test_function: TestFunction):
#         return f"""
# TEST_F({self.name}, {test_function.name}) {{
#     {test_function.body}
# }}
# """
#
#     # @property
#     # def inputs(self):
#     #     return ...
#
#     @property
#     def outputs(self):
#         return ...
#
#     @property
#     def tests(self):
#         return sum(map(self._test_f_, self.test_functions), "")
#
#     pass


class VarType:
    # TODO: add __eq__ to both VarType and ADVarType
    # TODO: add documentation to both VarType and ADVarType
    alias: str
    shortname: str
    definition: str
    test: str
    generator: Callable[[], Any]

    # TODO: replace with __new__ to avoid duplicates and redefinitions

    def __init__(self, alias: str, shortname: str, definition: str, test: str, generator: Callable[[], Any]):
        self.alias = alias
        self.shortname = shortname
        self.definition = definition
        self.test = test
        self.generator = generator
        pass

    pass


class ADVarType:
    alias: str
    shortname: str
    definition: str
    parent: VarType

    # NOTE: this REQUIRES that this type be constructed as:
    #   <alias> <name>(<parent_obj>, <parent_b_obj>);
    # EX:
    #   ADVec_t x_ad(x, xb);
    # Where x and xb are Vec_t types

    # TODO: replace with __new__ to avoid duplicates and redefinitions

    def __init__(self, alias: str, shortname: str, definition: str, parent: VarType):
        self.alias = alias
        self.shortname = shortname
        self.definition = definition
        self.parent = parent
        pass

    @property
    def test(self):
        return self.parent.test

    pass


io_type = List[Tuple[str, ADVarType]]  # [(<var_name>, <var_type>), ...]
non_constant_inputs_type = Set[str]  # {<var_name>, ...}  <-These are the active inputs


class TestFunction:
    name: str
    operation: types.FunctionType  # TODO: format
    operation_name: str
    inputs: io_type  # [(<var_name>, <var_type>), ...]
    outputs: io_type  # [(<var_name>, <var_type>), ...]
    variants: List[non_constant_inputs_type]

    # returns: Optional[...]  # This can be used if the function should return something (e.g. a scalar)

    def __init__(self, name: str, operation: types.FunctionType, operation_name: str,
                 inputs: io_type, outputs: io_type, variants: List[non_constant_inputs_type]):
        self.name = name
        # TODO: should operation_name just be name?
        self.operation_name = operation_name
        self.operation = operation
        self.inputs = inputs
        self.outputs = outputs
        self.variants = variants
        pass

    # TODO: figure out how to nest tests so, for example, we can have all the Dot product variations under a single tab
    #  This should be some variation on the "full_test_variant" method, and possibly the "_test_function_" method in
    #  TestConstructor

    # TODO: replace properties with static properties where applicable

    @property
    def datatypes(self) -> Set[ADVarType]:
        # datatypes = set(list(zip(*self.inputs))[1]).union(list(zip(*self.outputs))[1])
        datatypes = self.input_types
        datatypes.update(self.output_types)
        return datatypes

    @property
    def input_types(self) -> Set[ADVarType]:
        return {var_type for var_name, var_type in self.inputs}

    @property
    def output_types(self) -> Set[ADVarType]:
        return {var_type for var_name, var_type in self.outputs}

    def _test_type_(self, non_constant_inputs: non_constant_inputs_type) -> str:
        modifier = ''.join(var_type.shortname if var_name in non_constant_inputs else var_type.parent.shortname
                           for var_name, var_type in self.inputs
                           if var_name in non_constant_inputs)
        return f"{self.name}_{modifier}"

    @staticmethod
    def _all_declaration_format_(string_format: str, io_vars: io_type, var_type: ADVarType) -> List[str]:
        return [string_format.format(var_name=var_name, )
                for var_name, io_var_type in io_vars
                if io_var_type == var_type]  # This might need modification

    @staticmethod
    def _non_constant_declaration_format_(string_format: str, io_vars: io_type, var_type: ADVarType,
                                          non_constant_inputs: non_constant_inputs_type) -> List[str]:
        return [string_format.format(var_name=var_name, )
                for var_name, io_var_type in io_vars
                if (io_var_type == var_type and  # This might need modification
                    var_name in non_constant_inputs)]

    def _evaluation_signature_(self, non_constant_inputs: non_constant_inputs_type):
        return ', '.join(
            [  # Inputs
                f"{var_name}_ad" if (var_name in non_constant_inputs) else f"{var_name}"
                for var_name, var_type in self.inputs
            ] +
            [  # Outputs
                f"{var_name}_ad" if non_constant_inputs else f"{var_name}"
                # ^ If any of the inputs are non-constant, then all the outputs are non-constant
                for var_name, var_type in self.outputs
            ]
        )

    @staticmethod
    def _test_f_(test_type: str, test_name: str,
                 declarations_list: List[str], evaluations_list: List[str], comparisons_list: List[str]) -> str:
        separator_string = '\n    '
        declarations = separator_string.join(declarations_list)
        evaluations = separator_string.join(evaluations_list)
        comparisons = separator_string.join(comparisons_list)
        return f"""
TEST_F({test_type}, {test_name}) {{
    // Declarations and Initializations:
    {declarations}
    // Evaluations:
    {evaluations}
    // Comparisons:
    {comparisons}
}}
"""

    def _test_f_passive_(self, test_type: str, non_constant_inputs: non_constant_inputs_type) -> str:
        non_constant_input_types = {var_type for var_name, var_type in self.inputs if var_name in non_constant_inputs}
        declarations_list = (
                [  # initialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard inputs
                        self._all_declaration_format_(
                            "{var_name}({var_name}_data)", self.inputs, var_type
                        )
                    ) +
                    ";"
                    for var_type in self.input_types
                ] +
                [  # uninitialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard outputs
                        self._all_declaration_format_(
                            "{var_name}", self.outputs, var_type
                        ) +
                        # "b" outputs (FYI: if any of the inputs are non-constant, then all outputs are non-constant)
                        (self._all_declaration_format_(
                            "{var_name}b", self.outputs, var_type
                        ) * bool(non_constant_inputs)) +
                        # "b" inputs (for the non-constant inputs)
                        self._non_constant_declaration_format_(
                            "{var_name}b", self.inputs, var_type, non_constant_inputs
                        )
                    ) +
                    ";"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ]
        )

        evaluations_list = [
            f'auto expr = A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)});'
        ]

        comparisons_list = (  # This depends on "test_name" (e.g. passive, forward, etc...)
            [
                f"{var_type.test}({var_name}, {var_name}_out);"
                for var_name, var_type in self.outputs
            ]
        )
        return self._test_f_(test_type, "passive", declarations_list, evaluations_list, comparisons_list)

    def _test_f_forward_(self, test_type: str, non_constant_inputs: non_constant_inputs_type) -> str:
        non_constant_input_types = {var_type for var_name, var_type in self.inputs if var_name in non_constant_inputs}
        declarations_list = (
                [  # initialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard inputs
                        self._all_declaration_format_(
                            "{var_name}({var_name}_data)", self.inputs, var_type
                        ) +
                        # "b" inputs (for the non-constant inputs)
                        self._non_constant_declaration_format_(
                            "{var_name}b({var_name}b_data)", self.inputs, var_type, non_constant_inputs
                        )
                    ) +
                    ";"
                    for var_type in self.input_types
                ] +
                [  # uninitialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard outputs
                        self._all_declaration_format_(
                            "{var_name}", self.outputs, var_type
                        ) +
                        # "b" outputs (FYI: if any of the inputs are non-constant, then all outputs are non-constant)
                        (self._all_declaration_format_(
                            "{var_name}b", self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";"
                    for var_type in self.output_types
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ]
        )

        evaluations_list = [
            f'auto expr = A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)});',
            f'expr.forward();',
        ]

        comparisons_list = (  # This depends on the type of test (e.g. passive, forward, etc...)
                [
                    f"{var_type.test}({var_name}, {var_name}_out);"
                    for var_name, var_type in self.outputs
                ] +
                [
                    f"{var_type.test}({var_name}b, {var_name}b_out);"
                    for var_name, var_type in self.outputs
                ]
        )
        return self._test_f_(test_type, "forward", declarations_list, evaluations_list, comparisons_list)

    def _test_f_reverse_(self, test_type: str, non_constant_inputs: non_constant_inputs_type) -> str:
        non_constant_input_types = {var_type for var_name, var_type in self.inputs if var_name in non_constant_inputs}
        declarations_list = (
                [  # initialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard inputs
                        self._all_declaration_format_(
                            "{var_name}({var_name}_data)", self.inputs, var_type
                        ) +
                        # "b" outputs (FYI: if any of the inputs are non-constant, then all outputs are non-constant)
                        (self._all_declaration_format_(
                            "{var_name}b({var_name}b_data)", self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";"
                    for var_type in self.input_types
                ] +
                [  # uninitialized declarations
                    f"{var_type.parent.alias} " +
                    ', '.join(
                        # standard outputs
                        self._all_declaration_format_(
                            "{var_name}", self.outputs, var_type
                        ) +
                        # "b" inputs (for the non-constant inputs)
                        self._non_constant_declaration_format_(
                            "{var_name}b", self.inputs, var_type, non_constant_inputs
                        )
                    ) +
                    ";"
                    for var_type in self.output_types
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)", self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ]
        )

        evaluations_list = [
            f'auto expr = A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)});',
            f'expr.reverse();',
        ]

        comparisons_list = (  # This depends on "test_name" (e.g. passive, forward, etc...)
                [
                    f"{var_type.test}({var_name}, {var_name}_out);"
                    for var_name, var_type in self.outputs
                ] +
                [
                    f"{var_type.test}({var_name}b, {var_name}b_out);"
                    for var_name, var_type in self.inputs
                    if var_name in non_constant_inputs
                ]
        )
        return self._test_f_(test_type, "reverse", declarations_list, evaluations_list, comparisons_list)

    def full_test_variant(self, non_constant_inputs: non_constant_inputs_type) -> str:
        test_type = self._test_type_(non_constant_inputs)
        separator_string = '\n        '
        # TODO: generate outputs
        if non_constant_inputs:
            # Include derivatives
            results = (
                    [
                        ...
                    ] +
                    [
                        ...
                    ]
            )
        else:
            # No derivatives necessary
            results = (
                    [
                        ...
                    ] +
                    [
                        ...
                    ]
            )

        result_string = f"""
class {test_type} : public {self.name} {{
    protected:
        // Results
        {separator_string.join(results)}
}};
{self._test_f_passive_(test_type, non_constant_inputs)}"""

        if non_constant_inputs:
            return result_string + \
                   self._test_f_forward_(test_type, non_constant_inputs) + \
                   self._test_f_reverse_(test_type, non_constant_inputs)
        return result_string

    @property
    def tests(self) -> str:
        tests = [self.full_test_variant(non_constant_inputs) for non_constant_inputs in self.variants]
        return ''.join(tests)

    pass


class TestConstructor:
    name: str
    packages: List[str]
    typedefs: Dict[str, str]
    test_functions: List[TestFunction]

    def __init__(self, name: str, packages: List[str], typedefs: Dict[str, str], test_functions: List[TestFunction]):
        # TODO: derive typedefs from test_functions
        # TODO: add inspection for use of all items in all packages
        self.name = name
        self.packages = packages
        self.typedefs = typedefs
        self.test_functions = test_functions
        pass

    def _test_function_(self, test_function: TestFunction):
        return f"""
class {test_function.name} : public {self.name}Test {{
    protected:
}};
{test_function.tests}"""

    @property
    def _include_statements_(self):
        includes = '\n'.join(f'#include "{pkg}"' for pkg in self.packages)
        return f"""
#include <gtest/gtest.h>

#include "a2dobjs.h"
#include "a2dtypes.h"
{includes}
#include "test_commons.h"
"""

    @property
    def _type_definitions_(self):
        # put typedefs in order based on precedence
        names = []
        types_ = []
        for name, type_ in self.typedefs.items():
            if any(name in typename for typename in types_):
                position = [name in typename for typename in types_].index(True)
                names.insert(position, name)
                types_.insert(position, type_)
            else:
                names.append(name)
                types_.append(type_)
            pass
        defs = '\n'.join(f'using {name} = {type_};' for name, type_ in zip(names, types_))
        return f"""
{defs}
"""

    @property
    def _testing_input_class_(self):
        # TODO
        inputs = ...
        return f"""
class {self.name}Test : public ::testing::Test {{
    protected:
        // Input Options:
        {inputs}
}};
"""

    @property
    def _all_tests_(self):
        return ''.join(map(self._test_function_, self.test_functions))

    def construct(self):
        file_str = self._include_statements_ + self._type_definitions_ + self._testing_input_class_ + self._all_tests_
        # TODO: make this write the file instead of just returning the string
        return file_str

    pass


if __name__ == '__main__0':
    testConstructor = TestConstructor(name='VecOps', packages=['a2dvecops3d.h'], typedefs={
        'T': 'double',
        'I': 'int',
        'Vec_t': 'A2D::Vec<T, 3>',
        'ADVec_t': 'A2D::ADVec<A2D::Vec<T, 3>>',
        'ADScalar_t': 'A2D::ADScalar<T>',
    }, test_functions=[])
    print(testConstructor.construct())
    pass

if __name__ == '__main__0':
    vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>', lambda: numpy.random.random(3))
    advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)

    # name: str
    # operation: types.FunctionType  # signature must be operation(input1, input2, ...) -> Tuple[output1, output2, ...]
    # operation_name: str
    # inputs: io_type  # {<var_name>: <var_type>, ...}
    # outputs: io_type  # {<var_name>: <var_type>, ...}
    # variants: List[non_constant_inputs_type]
    name = 'Vec3Cross'
    operation = lambda x, y: numpy.cross(x, y)
    operation_name = 'Vec3Cross'
    inputs = {"x": advec_t, "y": advec_t}
    outputs = {"v": advec_t}

    # non_constant_inputs = {}  # Passive only
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data);"
    # uninitialized declarations
    "Vec_t v;"
    # dependent declarations (none)
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x, y, v);"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out)"

    # non_constant_inputs = {"x", "y"}
    #                       PASSIVE:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);"
    # uninitialized declarations
    "Vec_t v, vb;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    #                       FORWARD:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);"
    # uninitialized declarations
    "Vec_t v, vb;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
    "expr.forward();"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    "expect_vec_eq<3>(vb, vb_out);"
    #                       REVERSE:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), vb(vb_data);"
    # uninitialized declarations
    "Vec_t xb, yb, v;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
    "expr.reverse();"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    "expect_vec_eq<3>(xb, xb_out);"
    "expect_vec_eq<3>(yb, yb_out);"

    # non_constant_inputs = {"x"}
    #                       PASSIVE:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), xb(xb_data);"
    # uninitialized declarations
    "Vec_t v, vb;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    #                       FORWARD:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), xb(xb_data);"
    # uninitialized declarations
    "Vec_t v, vb;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
    "expr.forward();"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    "expect_vec_eq<3>(vb, vb_out);"
    #                       REVERSE:
    "// Declarations and Initializations:"
    # initialized declarations
    "Vec_t x(x_data), y(y_data), vb(vb_data);"
    # uninitialized declarations
    "Vec_t xb, v;"
    # dependent declarations
    "ADVec_t x_ad(x, xb), v_ad(v, vb);"
    "// Evaluations:"
    "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
    "expr.reverse();"
    "// Comparisons:"
    "expect_vec_eq<3>(v, v_out);"
    "expect_vec_eq<3>(xb, xb_out);"

    pass

if __name__ == '__main__':
    vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>', lambda: numpy.random.random(3))
    advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)

    tf = TestFunction("Vec3Cross", numpy.cross, "Vec3Cross",
                      inputs=[('x', advec_t), ('y', advec_t)],
                      outputs=[('v', advec_t), ],
                      variants=[{'x', 'y'}, set()])

    non_constants = {'x', 'y'}
    print(
        tf._test_f_passive_(tf._test_type_(non_constants), non_constants),
        '\n',
        tf._test_f_forward_(tf._test_type_(non_constants), non_constants),
        '\n',
        tf._test_f_reverse_(tf._test_type_(non_constants), non_constants),
    )
    pass
