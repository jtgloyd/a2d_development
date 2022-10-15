import itertools
import os
from typing import List, Dict, Callable, Any, Set, Tuple, Union
import numpy

# TODO: replace properties with static properties where applicable

# TODO: for AD variables, convert:
#       expect_<type>_eq<template>(x, x_out);
#       expect_<type>_eq<template>(xb, xb_out);
#   To:
#       expect_<type>_eq<template>(x_ad.value(), x_out);
#       expect_<type>_eq<template>(x_ad.bvalue(), xb_out);


var_generator_type = Callable[[], numpy.ndarray]


class VarType:
    """\
generator must be a zero-argument function returning a numpy array of values.  The function must return a numpy array \
in order to be compatible with the complex step method implementations.  The values returned by the "generator" \
function should be sufficient to initialize a random instance of the variable type when formatted as a variadic \
argument to the "initialize_format" string using the str.format method
    Ex. self.initialize_format.format(*self.generator(), **kwargs)
"""

    __instances_by_alias__: Dict[str, "VarType"] = {}

    # TODO: add documentation to both VarType and ADVarType
    alias: str
    shortname: str
    definition: str
    test: str
    initialize_assignment_format: str
    generator: var_generator_type

    def __init__(self,
                 alias: str,
                 shortname: str,
                 definition: str,
                 test: str,
                 initialize_assignment_format: str,
                 generator: var_generator_type,
                 ):
        self.alias = alias
        self.shortname = shortname
        self.definition = definition
        self.test = test
        self.initialize_assignment_format = initialize_assignment_format
        self.generator = generator
        pass

    def __new__(cls,
                alias: str,
                shortname: str,
                definition: str,
                test: str,
                initialize_assignment_format: str,
                generator: var_generator_type,
                ):
        if alias in cls.__instances_by_alias__:
            equivalence = [getattr(cls.__instances_by_alias__[alias], key) == locals()[key]
                           for key in cls.__comparison_keys__()]
            if all(equivalence):
                # TODO: check generator
                return cls.__instances_by_alias__[alias]
            raise ValueError(f'Two different VarType objects with the same alias are not allowed.  There is already\n'
                             f'a VarType object with the alias "{alias}" with different attributes than were defined.')
        if alias in ADVarType.__instances_by_alias__:
            raise ValueError(f'A VarType object cannot have the same alias as a ADVarType object.')

        obj = object.__new__(cls)
        cls.__instances_by_alias__[alias] = obj
        return obj

    def __eq__(self, other):
        if isinstance(other, VarType):
            equivalence = all(getattr(self, key) == getattr(other, key)
                              for key in self.__comparison_keys__())
            return equivalence
        return False

    def __hash__(self):
        return sum(map(hash, (
            getattr(self, key)
            for key in self.__comparison_keys__().union(['generator'])
        )))

    @classmethod
    def __comparison_keys__(cls):
        return set(cls.__init__.__annotations__.keys()).difference(['generator'])

    pass


class ADVarType:
    __instances_by_alias__: Dict[str, "ADVarType"] = {}

    alias: str
    shortname: str
    definition: str
    get_value: str
    get_bvalue: str
    # initialization_format: str
    parent: VarType
    # requires_parent_declaration: bool
    initialization_defaults: Union[Tuple[Any, Any], Tuple[()]]

    # NOTE: this REQUIRES that this type be constructed as:
    #   <alias> <name>(<parent_obj>, <parent_b_obj>);
    # EX:
    #   ADVec_t x_ad(x, xb);
    # Where x and xb are Vec_t types

    def __init__(self,
                 alias: str,
                 shortname: str,
                 definition: str,
                 get_value: str,
                 get_bvalue: str,
                 # initialization_format: str,
                 parent: VarType,
                 # requires_parent_declaration: bool,
                 initialization_defaults: Union[Tuple[Any, Any], Tuple[()]] = (),
                 ):
        self.alias = alias
        self.shortname = shortname
        self.definition = definition
        self.get_value = get_value
        self.get_bvalue = get_bvalue
        # self.initialization_format = initialization_format
        self.parent = parent
        # self.requires_parent_declaration = requires_parent_declaration
        self.initialization_defaults = initialization_defaults
        pass

    def __new__(cls,
                alias: str,
                shortname: str,
                definition: str,
                get_value: str,
                get_bvalue: str,
                # initialization_format: str,
                parent: VarType,
                # requires_parent_declaration: bool,
                initialization_defaults: Union[Tuple[Any, Any], Tuple[()]] = (),
                ):
        if alias in cls.__instances_by_alias__:
            equivalence = all(getattr(cls.__instances_by_alias__[alias], key) == locals()[key]
                              for key in cls.__comparison_keys__())
            if equivalence:
                return cls.__instances_by_alias__[alias]
            raise ValueError(f'Two different ADVarType objects with the same alias are not allowed.  There is already\n'
                             f'an ADVarType object with the alias "{alias}" with different attributes than were given.')
        if alias in VarType.__instances_by_alias__:
            raise ValueError(f'An ADVarType object cannot have the same alias as a VarType object.')

        obj = object.__new__(cls)
        cls.__instances_by_alias__[alias] = obj
        return obj

    @property
    def test(self):
        return self.parent.test

    @property
    def initialize_assignment_format(self):
        return self.parent.initialize_assignment_format

    def __eq__(self, other):
        if isinstance(other, ADVarType):
            equivalence = all(getattr(self, key) == getattr(other, key)
                              for key in self.__comparison_keys__())
            return equivalence
        return False

    def __hash__(self):
        return sum(map(hash, (
            getattr(self, key)
            for key in self.__comparison_keys__()
        )))

    @classmethod
    def __comparison_keys__(cls):
        return cls.__init__.__annotations__.keys()

    @property
    def requires_parent_declaration(self):
        return self.initialization_defaults == ()

    pass


class VariableOverloadError(Exception):
    """Multiple types (VarTypes and/or ADVarTypes) assigned to same variable name."""
    pass


class NamingConventionConflict(Exception):
    """Collision of variable names for given naming convention."""
    pass


io_type = List[Tuple[str, ADVarType]]  # [(<var_name>, <var_type>), ...]
non_constant_inputs_type = Set[str]  # {<var_name>, ...}  <-These are the active inputs
input_data_type = Dict[str, Tuple[Any, ADVarType]]  # {<var_name>: (<value>, <var_type>), ...}
operation_type = Callable[..., Tuple[numpy.ndarray, ...]]


class TestFunction:
    __h__ = 1e-30

    operation_name: str
    operation: operation_type  # TODO: format
    # TODO: ^DOCUMENT
    #   *Must return iterable of outputs, even when there is just a single output
    inputs: io_type  # [(<var_name>, <var_type>), ...]
    outputs: io_type  # [(<var_name>, <var_type>), ...]
    variants: List[non_constant_inputs_type]

    def __init__(self,
                 operation_name: str,
                 inputs: io_type,
                 outputs: io_type,
                 operation: operation_type,
                 variants: List[non_constant_inputs_type],
                 ):
        self.operation_name = operation_name
        self.operation = operation
        # TODO: add signature check for operation based on inputs and outputs
        self.inputs = inputs
        self.outputs = outputs
        # TODO: generate expected variants (ignoring duplicates by symmetry) and check against variants list, then
        #  print a warning message if they do not match.
        self.variants = variants
        pass

    # TODO: figure out how to nest tests so, for example, we can have all the Dot product variations under a single tab
    #  This should be some variation on the "full_test_variant" method, and possibly the "_test_function_" method in
    #  TestConstructor

    def evaluate_at(self, input_data: input_data_type):
        kwargs = {var_name: input_data[var_name][0]
                  for var_name, var_type in self.inputs}
        return self.operation(**kwargs)

    # TODO: add comparison check between complex step method and finite difference method in case there are
    #  situations where the complex step method fails

    def evaluate_output_derivatives_at(self, input_data: input_data_type,
                                       non_constant_inputs: non_constant_inputs_type):
        kwargs = {
            var_name: (
                input_data[var_name][0] + (1j * self.__h__ * input_data[f"{var_name}b"][0])
                if var_name in non_constant_inputs else
                input_data[var_name][0]
            )
            for var_name, var_type in self.inputs
        }
        return [numpy.imag(x) / self.__h__ for x in self.operation(**kwargs)]

    def evaluate_input_derivatives_at(self, input_data: input_data_type,
                                      non_constant_inputs: non_constant_inputs_type):
        output_names = next(zip(*self.outputs))  # TODO: this can be made into static property of the TestFunction class
        dimension_vectors = {
            var_name: [numpy.reshape(dim, numpy.shape(input_data[var_name][0]))
                       for dim in numpy.identity(numpy.size(input_data[var_name][0]))]
            for var_name, var_type in self.inputs
            if var_name in non_constant_inputs
        }  # TODO: this can be made into static property of the TestFunction class
        partial_derivatives = {
            candidate_var_name: [
                {output_name: numpy.imag(x) / self.__h__
                 for output_name, x in
                 zip(output_names, self.operation(**{
                     var_name: (
                         input_data[var_name][0] + (1j * self.__h__ * dimension_vector)
                         if var_name == candidate_var_name else
                         input_data[var_name][0]
                     )
                     for var_name, var_type in self.inputs
                 }))}
                for dimension_vector in dimension_vectors[candidate_var_name]
            ]
            for candidate_var_name, candidate_type in self.inputs
            if candidate_var_name in non_constant_inputs
        }

        results = {
            candidate_var_name: numpy.reshape([
                sum(numpy.sum(numpy.multiply(input_data[f"{output_name}b"][0], derivative))
                    for output_name, derivative in partial.items())
                for partial in partials
            ], numpy.shape(input_data[candidate_var_name][0]))
            for candidate_var_name, partials in partial_derivatives.items()
        }

        return [results[var_name]
                for var_name, var_type in self.inputs
                if var_name in non_constant_inputs]

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

    def _test_variant_name_(self, non_constant_inputs: non_constant_inputs_type) -> str:
        modifier = ''.join(var_type.shortname if var_name in non_constant_inputs else var_type.parent.shortname
                           for var_name, var_type in self.inputs
                           # if var_name in non_constant_inputs
                           )
        return f"{self.operation_name}_{modifier}"

    @staticmethod
    def _all_declaration_format_(string_format: str, io_vars: io_type, var_type: ADVarType) -> List[str]:
        defaults = dict(zip(['default_value', 'default_bvalue'], var_type.initialization_defaults))
        return [string_format.format(var_name=var_name, **defaults)
                for var_name, io_var_type in io_vars
                if io_var_type == var_type]  # This might need modification

    @staticmethod
    def _non_constant_declaration_format_(string_format: str, io_vars: io_type, var_type: ADVarType,
                                          non_constant_inputs: non_constant_inputs_type) -> List[str]:
        defaults = dict(zip(['default_value', 'default_bvalue'], var_type.initialization_defaults))
        return [string_format.format(var_name=var_name, **defaults)
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
    def _test_f_(test_variant_name: str, test_type: str,
                 declarations_list: List[str], evaluations_list: List[str], comparisons_list: List[str]) -> str:
        separator_string = '\n    '
        declarations = separator_string.join(declarations_list)
        evaluations = separator_string.join(evaluations_list)
        comparisons = separator_string.join(comparisons_list)
        return f"""
TEST_F({test_variant_name}, {test_type}) {{
    // Declarations and Initializations:
    {declarations}
    // Evaluations:
    {evaluations}
    // Comparisons:
    {comparisons}
}}
"""

    def _test_f_passive_(self, test_variant_name: str, non_constant_inputs: non_constant_inputs_type) -> str:
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
                    ";  /*UNQ_TF_TFP_01*/"
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
                    ";  /*UNQ_TF_TFP_02*/"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if ((var_type in self.output_types or
                         var_type in non_constant_input_types) and
                        (var_type.requires_parent_declaration or
                         not bool(non_constant_inputs)))
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)" if var_type.requires_parent_declaration else
                            "{var_name}_ad({var_name}, {default_bvalue})",
                            self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)" if var_type.requires_parent_declaration else
                            "{var_name}_ad({default_value}, {default_bvalue})",
                            self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";  /*UNQ_TF_TFP_03*/"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if ((var_type in self.output_types and bool(non_constant_inputs)) or
                        var_type in non_constant_input_types)
                ]
        )

        auto_typing = 'auto expr = ' if bool(non_constant_inputs) else ''
        evaluations_list = [
            f'{auto_typing}A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)})'
            f';  /*UNQ_TF_TFP_04*/'
        ]

        comparisons_list = (  # This depends on type of test (e.g. passive, forward, etc...)
            [
                f"{var_type.test}({var_name}_ad{var_type.get_value}, {var_name}_out);  /*UNQ_TF_TFP_05*/"
                for var_name, var_type in self.outputs
            ] if bool(non_constant_inputs) else
            [
                f"{var_type.test}({var_name}, {var_name}_out);  /*UNQ_TF_TFP_06*/"
                for var_name, var_type in self.outputs
            ]
        )
        return self._test_f_(test_variant_name, "passive", declarations_list, evaluations_list, comparisons_list)

    def _test_f_forward_(self, test_variant_name: str, non_constant_inputs: non_constant_inputs_type) -> str:
        assert bool(non_constant_inputs)  # this might need to change later
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
                    ";  /*UNQ_TF_TFF_01*/"
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
                    ";  /*UNQ_TF_TFF_02*/"
                    for var_type in self.output_types
                    if var_type.requires_parent_declaration
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)",
                            self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)" if var_type.requires_parent_declaration else
                            "{var_name}_ad({default_value}, {default_bvalue})",
                            self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";  /*UNQ_TF_TFF_03*/"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ]
        )

        evaluations_list = [
            f'auto expr = A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)})'
            f';  /*UNQ_TF_TFF_04*/',
            f'expr.forward();  /*UNQ_TF_TFF_05*/',
        ]

        comparisons_list = (  # This depends on the type of test (e.g. passive, forward, etc...)
                [
                    f"{var_type.test}({var_name}_ad{var_type.get_value}, {var_name}_out);  /*UNQ_TF_TFF_06*/"
                    for var_name, var_type in self.outputs
                ] +
                [
                    f"{var_type.test}({var_name}_ad{var_type.get_bvalue}, {var_name}b_out);  /*UNQ_TF_TFF_07*/"
                    for var_name, var_type in self.outputs
                ]
        )
        return self._test_f_(test_variant_name, "forward", declarations_list, evaluations_list, comparisons_list)

    def _test_f_reverse_(self, test_variant_name: str, non_constant_inputs: non_constant_inputs_type) -> str:
        assert bool(non_constant_inputs)  # this might need to change later
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
                    ";  /*UNQ_TF_TFR_01*/"
                    for var_type in self.datatypes
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
                    ";  /*UNQ_TF_TFR_02*/"
                    for var_type in self.datatypes
                    if (var_type.requires_parent_declaration and
                        (var_type in non_constant_input_types or
                         var_type in self.output_types))
                ] +
                [  # dependent declarations (A.K.A. AD declarations)
                    f"{var_type.alias} " +
                    ', '.join(
                        self._non_constant_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)" if var_type.requires_parent_declaration else
                            "{var_name}_ad({var_name}, {default_bvalue})",
                            self.inputs, var_type, non_constant_inputs
                        ) +
                        (self._all_declaration_format_(
                            "{var_name}_ad({var_name}, {var_name}b)" if var_type.requires_parent_declaration else
                            "{var_name}_ad({default_value}, {var_name}b)",
                            self.outputs, var_type
                        ) * bool(non_constant_inputs))
                    ) +
                    ";  /*UNQ_TF_TFR_03*/"
                    for var_type in self.datatypes
                    # Make sure this declaration isn't empty
                    if var_type in self.output_types or var_type in non_constant_input_types
                ]
        )

        evaluations_list = [
            f'auto expr = A2D::{self.operation_name}({self._evaluation_signature_(non_constant_inputs)})'
            f';  /*UNQ_TF_TFR_04*/',
            f'expr.reverse();  /*UNQ_TF_TFR_05*/',
        ]

        comparisons_list = (  # This depends on type of test (e.g. passive, forward, etc...)
                [
                    f"{var_type.test}({var_name}_ad{var_type.get_value}, {var_name}_out);  /*UNQ_TF_TFR_06*/"
                    for var_name, var_type in self.outputs
                ] +
                [
                    f"{var_type.test}({var_name}_ad{var_type.get_bvalue}, {var_name}b_out);  /*UNQ_TF_TFR_07*/"
                    for var_name, var_type in self.inputs
                    if var_name in non_constant_inputs
                ]
        )
        return self._test_f_(test_variant_name, "reverse", declarations_list, evaluations_list, comparisons_list)

    def full_test_variant(self, input_data: input_data_type,
                          non_constant_inputs: non_constant_inputs_type) -> str:
        test_variant_name = self._test_variant_name_(non_constant_inputs)
        separator_string = '\n    '

        # generate outputs
        if non_constant_inputs:
            nc_inputs = [(var_name, var_type)
                         for var_name, var_type in self.inputs
                         if var_name in non_constant_inputs]
            # Include derivatives
            results = (
                    [
                        # calculated nominal values
                        var_type.initialize_assignment_format.format(var_name=f"{var_name}_out", *value)
                        for (var_name, var_type), value in zip(self.outputs, self.evaluate_at(input_data))
                    ] +
                    [
                        # calculated output derivatives
                        var_type.initialize_assignment_format.format(var_name=f"{var_name}b_out", *value)
                        for (var_name, var_type), value in
                        zip(self.outputs, self.evaluate_output_derivatives_at(input_data, non_constant_inputs))
                    ] +
                    [
                        # calculated input derivatives
                        var_type.initialize_assignment_format.format(var_name=f"{var_name}b_out", *value)
                        for (var_name, var_type), value in
                        zip(nc_inputs, self.evaluate_input_derivatives_at(input_data, non_constant_inputs))
                    ]
            )
        else:
            # No derivatives necessary
            results = (
                [
                    # calculated nominal values
                    var_type.initialize_assignment_format.format(var_name=f"{var_name}_out", *value)
                    for (var_name, var_type), value in zip(self.outputs, self.evaluate_at(input_data))
                ]
            )

        test_string = f"""
class {test_variant_name} : public {self.operation_name} {{
protected:
    // Results
    {separator_string.join(results)}
}};  /*UNQ_TF_FTV_01*/
{self._test_f_passive_(test_variant_name, non_constant_inputs)}"""

        if non_constant_inputs:
            return test_string + \
                   self._test_f_forward_(test_variant_name, non_constant_inputs) + \
                   self._test_f_reverse_(test_variant_name, non_constant_inputs)
        return test_string

    def tests(self, input_data: input_data_type) -> str:
        tests = [self.full_test_variant(input_data, non_constant_inputs)
                 for non_constant_inputs in self.variants]
        return ''.join(tests)

    pass


class TestConstructor:
    name: str
    packages: List[str]
    var_types: List[Union[VarType, ADVarType]]
    test_functions: List[TestFunction]

    # TODO: modify this to be able to generate multiple values for all tests at once
    #  This should be accomplished by creating x01, x02, ..., xNN, xb01, xb02, ...
    #  then copying the code for the various test functions with these modifications

    def __init__(self, name: str, packages: List[str], var_types: List[Union[VarType, ADVarType]],
                 test_functions: List[TestFunction]):
        # TODO: add inspection for use of all items in all packages
        self.name = name
        # TODO: format name more strictly
        self.packages = packages
        self.var_types = var_types
        self.test_functions = test_functions
        pass

    @property
    def typedefs(self) -> Set[Union[VarType, ADVarType]]:
        # get var_types from test_functions and combine with given var_types
        return set(self.var_types).union(
            *[
                test_function.datatypes
                for test_function in self.test_functions
            ],
            *[
                {datatype.parent for datatype in test_function.datatypes}
                for test_function in self.test_functions
            ]
        )

    def input_data(self) -> input_data_type:
        # gather all inputs and outputs and their types (and make sure there aren't conflicts)
        all_io = {}
        for test_function in self.test_functions:
            for var_name, var_type in itertools.chain(test_function.inputs, test_function.outputs):
                if var_name in all_io:
                    if all_io[var_name] != var_type:
                        raise VariableOverloadError(f'{var_name} assigned multiple non-equivalent types: '
                                                    f'{all_io[var_name]} and {var_type}')
                    # make sure <var_name>b is not in all_io
                    elif f"{var_name}b" in all_io:
                        raise NamingConventionConflict(f'Illegal variable name "{var_name}b" when a \n'
                                                       f'variable "{var_name}" is also defined.')
                    # make sure <var_name>[:-1] is not in all_io (when var_name ends with "b")
                    elif var_name[-1] == 'b' and var_name[:-1] in all_io:
                        raise NamingConventionConflict(f'Illegal variable name "{var_name}" when a \n'
                                                       f'variable "{var_name[:-1]}" is also defined.')
                else:
                    all_io[var_name] = var_type
                pass
            pass
        # TODO: type conflicts can be allowed, but they will need to be taken out of the full test class and put into
        #  the individual function test classes (i.e. those created by the _test_function_ method)

        # generate data
        data = {
            var_name: (var_type.parent.generator(), var_type)
            for var_name, var_type in all_io.items()
        }
        # generate derivative data
        data.update({
            f"{var_name}b": (var_type.parent.generator(), var_type)
            for var_name, var_type in all_io.items()
        })
        return data  # {<var_name>: (<value>, <var_type>), ...}

    def _test_function_(self, input_data: input_data_type, test_function: TestFunction):
        separator_string = '\n    '
        overloaded_data = []  # note: must combine overloaded_data with input_data to pass if implementing this
        return f"""
class {test_function.operation_name} : public {self.name}Test {{
protected:
    {separator_string.join(overloaded_data)}
}};  /*UNQ_TC_TF_01*/
{test_function.tests(input_data)}"""

    # Component Construction Methods:

    def _include_statements_(self):
        includes = '\n'.join(f'#include "{pkg}"' for pkg in self.packages)
        return f"""
#include <gtest/gtest.h>

#include "a2dobjs.h"
#include "a2dtypes.h"
{includes}
#include "test_commons.h"
"""

    def _type_definitions_(self):
        # put typedefs in order based on precedence
        aliases = []
        definitions = []
        for typedef in self.typedefs:
            if any(typedef.alias in typename for typename in definitions):
                position = [typedef.alias in typename for typename in definitions].index(True)
                aliases.insert(position, typedef.alias)
                definitions.insert(position, typedef.definition)
            else:
                aliases.append(typedef.alias)
                definitions.append(typedef.definition)
            pass
        # format type definitions
        defs = '\n'.join(f'using {alias} = {definition};  /*UNQ_TC_TD_01*/'
                         for alias, definition in zip(aliases, definitions))
        return f"""
{defs}
"""

    def _testing_input_class_(self, input_data: input_data_type):
        separator_string = '\n    '
        data = [
            var_type.initialize_assignment_format.format(var_name=f"{var_name}_data", *value)
            for var_name, (value, var_type) in input_data.items()
        ]
        return f"""
class {self.name}Test : public ::testing::Test {{
protected:
    // Input Options:
    {separator_string.join(data)}
}};  /*UNQ_TC_TIC_01*/
"""

    def _all_tests_(self, input_data: input_data_type):
        return ''.join(
            # map(self._test_function_, self.test_functions)
            self._test_function_(input_data, test_function)
            for test_function in self.test_functions
        )

    def construct(self, destination: str = None, name_override: str = None):
        input_data = self.input_data()
        file_str = (
                self._include_statements_() +
                self._type_definitions_() +
                self._testing_input_class_(input_data) +
                self._all_tests_(input_data)
        )
        if destination is None:
            return file_str
        filename = f"{self.name if name_override is None else name_override.strip().rstrip('.cpp')}.cpp"
        separator = os.altsep if os.altsep in destination else os.sep
        full_filename = destination.rstrip(separator) + separator + 'test_' + filename.lstrip('test_')
        with open(full_filename, 'w') as f:
            f.write(file_str)
            f.close()
        pass

    pass


# if __name__ == '__main__0':
#     testConstructor = TestConstructor(name='VecOps', packages=['a2dvecops3d.h'], typedefs={
#         'T': 'double',
#         'I': 'int',
#         'Vec_t': 'A2D::Vec<T, 3>',
#         'ADVec_t': 'A2D::ADVec<A2D::Vec<T, 3>>',
#         'ADScalar_t': 'A2D::ADScalar<T>',
#     }, test_functions=[])
#     print(testConstructor.construct())
#     pass

# if __name__ == '__main__0':
#     vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>', 'const T {var_name}[3] = {{{0}, {1}, {2}}};',
#                     lambda: numpy.random.random(3))
#     advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)
#
#     # name: str
#     # operation: types.FunctionType  # signature must be operation(input1, input2, ...) -> Tuple[output1, output2, ...]
#     # operation_name: str
#     # inputs: io_type  # {<var_name>: <var_type>, ...}
#     # outputs: io_type  # {<var_name>: <var_type>, ...}
#     # variants: List[non_constant_inputs_type]
#     name = 'Vec3Cross'
#     operation = lambda x, y: numpy.cross(x, y)
#     operation_name = 'Vec3Cross'
#     inputs = {"x": advec_t, "y": advec_t}
#     outputs = {"v": advec_t}
#
#     # non_constant_inputs = {}  # Passive only
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data);"
#     # uninitialized declarations
#     "Vec_t v;"
#     # dependent declarations (none)
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x, y, v);"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out)"
#
#     # non_constant_inputs = {"x", "y"}
#     #                       PASSIVE:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);"
#     # uninitialized declarations
#     "Vec_t v, vb;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     #                       FORWARD:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);"
#     # uninitialized declarations
#     "Vec_t v, vb;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
#     "expr.forward();"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     "expect_vec_eq<3>(vb, vb_out);"
#     #                       REVERSE:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), vb(vb_data);"
#     # uninitialized declarations
#     "Vec_t xb, yb, v;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), y_ad(y, yb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y_ad, v_ad);"
#     "expr.reverse();"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     "expect_vec_eq<3>(xb, xb_out);"
#     "expect_vec_eq<3>(yb, yb_out);"
#
#     # non_constant_inputs = {"x"}
#     #                       PASSIVE:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), xb(xb_data);"
#     # uninitialized declarations
#     "Vec_t v, vb;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     #                       FORWARD:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), xb(xb_data);"
#     # uninitialized declarations
#     "Vec_t v, vb;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
#     "expr.forward();"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     "expect_vec_eq<3>(vb, vb_out);"
#     #                       REVERSE:
#     "// Declarations and Initializations:"
#     # initialized declarations
#     "Vec_t x(x_data), y(y_data), vb(vb_data);"
#     # uninitialized declarations
#     "Vec_t xb, v;"
#     # dependent declarations
#     "ADVec_t x_ad(x, xb), v_ad(v, vb);"
#     "// Evaluations:"
#     "auto expr = A2D::Vec3Cross(x_ad, y, v_ad);"
#     "expr.reverse();"
#     "// Comparisons:"
#     "expect_vec_eq<3>(v, v_out);"
#     "expect_vec_eq<3>(xb, xb_out);"
#
#     pass

if __name__ == '__main__0':
    """Vec3Cross test construction:"""

    t_t = VarType('T', 'Scalar', 'double', 'expect_val_eq', 'const T {var_name} = {0};', lambda: numpy.random.random(1))
    i_t = VarType('I', 'Int', 'int', 'expect_val_eq', 'const T {var_name} = {0};',
                  lambda: numpy.random.randint(-256, 256, 1))
    vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>',
                    'const T {var_name}[3] = {{{0},\n{1},\n{2}}};', lambda: numpy.random.random(3))
    advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)
    adscalar_t = ADVarType('ADScalar_t', 'ADScalar', 'A2D::ADScalar<T>', t_t)

    tf = TestFunction("Vec3Cross", lambda x, y: (numpy.cross(x, y),),
                      inputs=[('x', advec_t), ('y', advec_t)],
                      outputs=[('v', advec_t), ],
                      variants=[{'x', 'y'}, set()])

    tc = TestConstructor("test", ["a2dvecops3d.h"], [t_t, i_t, vec_t, advec_t, adscalar_t],
                         [tf])

    inp_data = tc.input_data()
    print(
        # tf.tests(inp_data),
        tc.construct(),
    )
    pass

if __name__ == '__main__0':
    """Cross product complex step test:"""
    x_vec = numpy.random.random(3)
    y_vec = numpy.random.random(3)
    v_vec = numpy.cross(x_vec, y_vec)
    xb_vec = numpy.random.random(3)
    yb_vec = numpy.random.random(3)
    vb_vec = numpy.random.random(3)
    h = 1e-10

    # Forward
    print(
        "       Forward:",
        "Analytic:",
        numpy.cross(xb_vec, y_vec) + numpy.cross(x_vec, yb_vec),
        "Complex step:",
        numpy.imag(numpy.cross(x_vec + (1j * h * xb_vec), y_vec + (1j * h * yb_vec))) / h,
        sep='\n'
    )

    # Reverse
    print(
        "       Reverse:",
        "Analytic x:",
        numpy.cross(y_vec, vb_vec),
        "Complex step x:",
        numpy.imag(...) / h,
        '\n',
        "Analytic y:",
        numpy.cross(vb_vec, x_vec),
        "Complex step y:",
        numpy.imag(...) / h,
        sep='\n'
    )
    pass

if __name__ == '__main__0':
    """Set (hash) test"""

    t_t = VarType('T', 'Scalar', 'double', 'expect_val_eq', 'const T {var_name} = {0};', lambda: numpy.random.random(1))
    i_t = VarType('I', 'Int', 'int', 'expect_val_eq', 'const T {var_name} = {0};',
                  lambda: numpy.random.randint(-256, 256, 1))
    vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>', 'const T {var_name}[3] = {{{0}, {1}, {2}}};',
                    lambda: numpy.random.random(3))
    advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)
    adscalar_t = ADVarType('ADScalar_t', 'ADScalar', 'A2D::ADScalar<T>', t_t)

    tx = {t_t, i_t, vec_t, advec_t, adscalar_t}
    print(tx)
    pass

# if __name__ == '__main__':
#     """Reverse mode complex step development"""
#
#     t_t = VarType('T', 'Scalar', 'double', 'expect_val_eq',
#                   'const T {var_name} = {0};',
#                   lambda: numpy.random.random(1))
#     i_t = VarType('I', 'Int', 'int', 'expect_val_eq',
#                   'const T {var_name} = {0};',
#                   lambda: numpy.random.randint(-256, 256, 1))
#     vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>',
#                     'const T {var_name}[3] = {{{0}, {1}, {2}}};',
#                     lambda: numpy.random.random(3))
#     advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', vec_t)
#     adscalar_t = ADVarType('ADScalar_t', 'ADScalar', 'A2D::ADScalar<T>', t_t)
#
#     tf = TestFunction("Vec3Cross", lambda x, y: (numpy.cross(x, y),),
#                       inputs=[('x', advec_t), ('y', advec_t)],
#                       outputs=[('v', advec_t), ],
#                       variants=[{'x', 'y'}, set()])
#
#     tc = TestConstructor("test", ["a2dvecops3d.h"], [t_t, i_t, vec_t, advec_t, adscalar_t],
#                          [tf])
#
#     inp_data = tc.input_data()
#     non_constant_inputs = {'x', 'y'}
#
#     output_names = next(zip(*tf.outputs))
#     dimension_vectors = {
#         var_name: [numpy.reshape(dim, numpy.shape(inp_data[var_name][0]))
#                    for dim in numpy.identity(numpy.size(inp_data[var_name][0]))]
#         for var_name, var_type in tf.inputs
#         if var_name in non_constant_inputs
#     }
#     partial_derivatives = {
#         candidate_var_name: [
#             {output_name: numpy.imag(x) / tf.__h__
#              for output_name, x in
#              zip(output_names, tf.operation(**{
#                  var_name: (
#                      inp_data[var_name][0] + (1j * tf.__h__ * dimension_vector)
#                      if var_name == candidate_var_name else
#                      inp_data[var_name][0]
#                  )
#                  for var_name, var_type in tf.inputs
#              }))}
#             for dimension_vector in dimension_vectors[candidate_var_name]
#         ]
#         for candidate_var_name, candidate_type in tf.inputs
#         if candidate_var_name in non_constant_inputs
#     }
#
#     results = {
#         candidate_var_name: numpy.reshape([
#             sum(numpy.sum(numpy.multiply(inp_data[f"{output_name}b"][0], derivative))
#                 for output_name, derivative in partial.items())
#             for partial in partials
#         ], numpy.shape(inp_data[candidate_var_name][0]))
#         for candidate_var_name, partials in partial_derivatives.items()
#     }
#
#     true_results = {
#         'x': numpy.cross(inp_data['y'][0], inp_data['vb'][0]),
#         'y': numpy.cross(inp_data['vb'][0], inp_data['x'][0])
#     }
#     pass

if __name__ == '__main__':
    """Construction of vector_operation_development tests"""


    def symmat():
        non_sym = numpy.random.random((3, 3))
        return (non_sym + non_sym.T).flatten()


    t_t = VarType('T', 'Scalar', 'double', 'expect_val_eq', 'const T {var_name} = {0};', lambda: numpy.random.random(1))
    i_t = VarType('I', 'Int', 'int', 'expect_val_eq', 'const T {var_name} = {0};',
                  lambda: numpy.random.randint(-256, 256, 1))
    vec_t = VarType('Vec_t', 'Vec', 'A2D::Vec<T, 3>', 'expect_vec_eq<3>', 'const T {var_name}[3] = {{{0}, {1}, {2}}};',
                    lambda: numpy.random.random(3))
    # TODO: we should REALLY include a symmetric matrix type
    mat_t = VarType('Mat_t', 'Mat', 'A2D::Mat<T, 3, 3>', 'expect_mat_eq<3, 3>',
                    'const T {var_name}[9] = {{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}}};',
                    # lambda: numpy.random.random(9),
                    symmat,
                    )
    # TODO: make it so that we can include an "indent" variable in the initialize_assignment_format string so we can
    #  structure matrices better.
    advec_t = ADVarType('ADVec_t', 'ADVec', 'A2D::ADVec<Vec_t>', '.value()', '.bvalue()', vec_t)
    adscalar_t = ADVarType('ADScalar_t', 'ADScalar', 'A2D::ADScalar<T>', '.value', '.bvalue', t_t, (0, 0))
    admat_t = ADVarType('ADMat_t', 'ADMat', 'A2D::ADMat<Mat_t>', '.value()', '.bvalue()', mat_t)

    tfs = [
        TestFunction("Vec3Norm",
                     inputs=[('x', advec_t), ],
                     outputs=[('a', adscalar_t), ],
                     operation=lambda x: (numpy.array([numpy.dot(x, x) ** 0.5]),),
                     variants=[{'x'}, set()]),
        TestFunction("Vec3Scale",
                     inputs=[('x', advec_t),
                             ('a', adscalar_t), ],
                     outputs=[('v', advec_t), ],
                     operation=lambda x, a: (numpy.multiply(a, x),),
                     variants=[{'x', 'a'}, {'x'}, {'a'}, set()]),
        TestFunction("Vec3Dot",
                     inputs=[('x', advec_t),
                             ('y', advec_t), ],
                     outputs=[('a', adscalar_t), ],
                     operation=lambda x, y: (numpy.array([numpy.dot(x, y)]),),
                     variants=[{'x', 'y'}, {'x'}, set()]),
        TestFunction("Vec3Normalize",
                     inputs=[('x', advec_t), ],
                     outputs=[('v', advec_t), ],
                     operation=lambda x: (numpy.multiply(1 / (numpy.dot(x, x) ** 0.5), x),),
                     variants=[{'x'}, set()]),
        TestFunction("Vec3ScaleSymmetricOuterProduct",
                     inputs=[('a', adscalar_t),
                             ('x', advec_t), ],
                     outputs=[('S', admat_t), ],
                     operation=lambda a, x: (numpy.multiply(a, numpy.outer(x, x)).flatten(),),
                     variants=[{'a', 'x'}, {'a'}, {'x'}, set()])
    ]

    tc = TestConstructor("vector_operation_development", ["vector_operation_development.h"],
                         [t_t, i_t, vec_t, advec_t, adscalar_t],
                         tfs)

    # inp_data = tc.input_data()
    # print(
    #     tf.tests(inp_data),
    # )

    tc.construct('C:/Users/james/Documents/C++/VLRCOE/A2D/a2d-vector-operations/tests')
    pass
