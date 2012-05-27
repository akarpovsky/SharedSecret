/*
  File autogenerated by gengetopt version 2.22.5
  generated with the following command:
  gengetopt -i cmdline.ggo 

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FIX_UNUSED
#define FIX_UNUSED(X) (void) (X) /* avoid warnings for unused params */
#endif

#include <getopt.h>

#include "cmdline.h"

const char *gengetopt_args_info_purpose = "";

const char *gengetopt_args_info_usage = "Usage: shasec [OPTIONS]...";

const char *gengetopt_args_info_description = "Shasec is an implementation of a shared secret system proposed in \n\"Improvements in Geometry-Based Secret Image Sharing Approach with \nSteganography\" by Mustafa Ulutas, Vasif V. Nabiyev and Guzin Ulutas.";

const char *gengetopt_args_info_detailed_help[] = {
  "  -h, --help             Print help and exit",
  "      --detailed-help    Print help, including all details and hidden options, \n                           and exit",
  "  -V, --version          Print version and exit",
  "\n Group: actions",
  "  -d, --distribute       Distributes the secret",
  "  -r, --recovery         Recovers the secret",
  "      --secret=filename  Image path of a .bmp image",
  "  If the action is a distribution, the image represents the secret. However, if \n  the action is a recovery, the image is the path where the output will be \n  placed",
  "  -k, --keys=number      Number of keys to recover the secret  (possible \n                           values=\"2\", \"3\", \"4\")",
  "  -n, --number=number    Total number of shadows where the secret will be \n                           distributed  (possible values=\"3\", \"4\", \"5\", \n                           \"6\", \"7\", \"8\")",
  "      --dir=pathname     Directory where the images will be placed  \n                           (default=`./')",
  "  If the action is a distribution, the shadow images will be placed in this \n  directory. However, if the action is \n  a recovery, the image shadows will be taken from this directory",
    0
};

static void
init_help_array(void)
{
  gengetopt_args_info_help[0] = gengetopt_args_info_detailed_help[0];
  gengetopt_args_info_help[1] = gengetopt_args_info_detailed_help[1];
  gengetopt_args_info_help[2] = gengetopt_args_info_detailed_help[2];
  gengetopt_args_info_help[3] = gengetopt_args_info_detailed_help[3];
  gengetopt_args_info_help[4] = gengetopt_args_info_detailed_help[4];
  gengetopt_args_info_help[5] = gengetopt_args_info_detailed_help[5];
  gengetopt_args_info_help[6] = gengetopt_args_info_detailed_help[6];
  gengetopt_args_info_help[7] = gengetopt_args_info_detailed_help[8];
  gengetopt_args_info_help[8] = gengetopt_args_info_detailed_help[9];
  gengetopt_args_info_help[9] = gengetopt_args_info_detailed_help[10];
  gengetopt_args_info_help[10] = 0; 
  
}

const char *gengetopt_args_info_help[11];

typedef enum {ARG_NO
  , ARG_STRING
  , ARG_INT
} cmdline_parser_arg_type;

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error);

static int
cmdline_parser_required2 (struct gengetopt_args_info *args_info, const char *prog_name, const char *additional_error);

const char *cmdline_parser_keys_values[] = {"2", "3", "4", 0}; /*< Possible values for keys. */
const char *cmdline_parser_number_values[] = {"3", "4", "5", "6", "7", "8", 0}; /*< Possible values for number. */

static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->detailed_help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->distribute_given = 0 ;
  args_info->recovery_given = 0 ;
  args_info->secret_given = 0 ;
  args_info->keys_given = 0 ;
  args_info->number_given = 0 ;
  args_info->dir_given = 0 ;
  args_info->actions_group_counter = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->secret_arg = NULL;
  args_info->secret_orig = NULL;
  args_info->keys_orig = NULL;
  args_info->number_orig = NULL;
  args_info->dir_arg = gengetopt_strdup ("./");
  args_info->dir_orig = NULL;
  
}

static
void init_args_info(struct gengetopt_args_info *args_info)
{

  init_help_array(); 
  args_info->help_help = gengetopt_args_info_detailed_help[0] ;
  args_info->detailed_help_help = gengetopt_args_info_detailed_help[1] ;
  args_info->version_help = gengetopt_args_info_detailed_help[2] ;
  args_info->distribute_help = gengetopt_args_info_detailed_help[4] ;
  args_info->recovery_help = gengetopt_args_info_detailed_help[5] ;
  args_info->secret_help = gengetopt_args_info_detailed_help[6] ;
  args_info->keys_help = gengetopt_args_info_detailed_help[8] ;
  args_info->number_help = gengetopt_args_info_detailed_help[9] ;
  args_info->dir_help = gengetopt_args_info_detailed_help[10] ;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n",
     (strlen(CMDLINE_PARSER_PACKAGE_NAME) ? CMDLINE_PARSER_PACKAGE_NAME : CMDLINE_PARSER_PACKAGE),
     CMDLINE_PARSER_VERSION);
}

static void print_help_common(void) {
  cmdline_parser_print_version ();

  if (strlen(gengetopt_args_info_purpose) > 0)
    printf("\n%s\n", gengetopt_args_info_purpose);

  if (strlen(gengetopt_args_info_usage) > 0)
    printf("\n%s\n", gengetopt_args_info_usage);

  printf("\n");

  if (strlen(gengetopt_args_info_description) > 0)
    printf("%s\n\n", gengetopt_args_info_description);
}

void
cmdline_parser_print_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_help[i])
    printf("%s\n", gengetopt_args_info_help[i++]);
}

void
cmdline_parser_print_detailed_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_detailed_help[i])
    printf("%s\n", gengetopt_args_info_detailed_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);
}

void
cmdline_parser_params_init(struct cmdline_parser_params *params)
{
  if (params)
    { 
      params->override = 0;
      params->initialize = 1;
      params->check_required = 1;
      params->check_ambiguity = 0;
      params->print_errors = 1;
    }
}

struct cmdline_parser_params *
cmdline_parser_params_create(void)
{
  struct cmdline_parser_params *params = 
    (struct cmdline_parser_params *)malloc(sizeof(struct cmdline_parser_params));
  cmdline_parser_params_init(params);  
  return params;
}

static void
free_string_field (char **s)
{
  if (*s)
    {
      free (*s);
      *s = 0;
    }
}


static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{

  free_string_field (&(args_info->secret_arg));
  free_string_field (&(args_info->secret_orig));
  free_string_field (&(args_info->keys_orig));
  free_string_field (&(args_info->number_orig));
  free_string_field (&(args_info->dir_arg));
  free_string_field (&(args_info->dir_orig));
  
  

  clear_given (args_info);
}

/**
 * @param val the value to check
 * @param values the possible values
 * @return the index of the matched value:
 * -1 if no value matched,
 * -2 if more than one value has matched
 */
static int
check_possible_values(const char *val, const char *values[])
{
  int i, found, last;
  size_t len;

  if (!val)   /* otherwise strlen() crashes below */
    return -1; /* -1 means no argument for the option */

  found = last = 0;

  for (i = 0, len = strlen(val); values[i]; ++i)
    {
      if (strncmp(val, values[i], len) == 0)
        {
          ++found;
          last = i;
          if (strlen(values[i]) == len)
            return i; /* exact macth no need to check more */
        }
    }

  if (found == 1) /* one match: OK */
    return last;

  return (found ? -2 : -1); /* return many values or none matched */
}


static void
write_into_file(FILE *outfile, const char *opt, const char *arg, const char *values[])
{
  int found = -1;
  if (arg) {
    if (values) {
      found = check_possible_values(arg, values);      
    }
    if (found >= 0)
      fprintf(outfile, "%s=\"%s\" # %s\n", opt, arg, values[found]);
    else
      fprintf(outfile, "%s=\"%s\"\n", opt, arg);
  } else {
    fprintf(outfile, "%s\n", opt);
  }
}


int
cmdline_parser_dump(FILE *outfile, struct gengetopt_args_info *args_info)
{
  int i = 0;

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot dump options to stream\n", CMDLINE_PARSER_PACKAGE);
      return EXIT_FAILURE;
    }

  if (args_info->help_given)
    write_into_file(outfile, "help", 0, 0 );
  if (args_info->detailed_help_given)
    write_into_file(outfile, "detailed-help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->distribute_given)
    write_into_file(outfile, "distribute", 0, 0 );
  if (args_info->recovery_given)
    write_into_file(outfile, "recovery", 0, 0 );
  if (args_info->secret_given)
    write_into_file(outfile, "secret", args_info->secret_orig, 0);
  if (args_info->keys_given)
    write_into_file(outfile, "keys", args_info->keys_orig, cmdline_parser_keys_values);
  if (args_info->number_given)
    write_into_file(outfile, "number", args_info->number_orig, cmdline_parser_number_values);
  if (args_info->dir_given)
    write_into_file(outfile, "dir", args_info->dir_orig, 0);
  

  i = EXIT_SUCCESS;
  return i;
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  i = cmdline_parser_dump(outfile, args_info);
  fclose (outfile);

  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}

/** @brief replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = 0;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

static void
reset_group_actions(struct gengetopt_args_info *args_info)
{
  if (! args_info->actions_group_counter)
    return;
  
  args_info->distribute_given = 0 ;
  args_info->recovery_given = 0 ;

  args_info->actions_group_counter = 0;
}

int
cmdline_parser (int argc, char **argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser_ext (int argc, char **argv, struct gengetopt_args_info *args_info,
                   struct cmdline_parser_params *params)
{
  int result;
  result = cmdline_parser_internal (argc, argv, args_info, params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser2 (int argc, char **argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;
  struct cmdline_parser_params params;
  
  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  result = cmdline_parser_internal (argc, argv, args_info, &params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  int result = EXIT_SUCCESS;

  if (cmdline_parser_required2(args_info, prog_name, 0) > 0)
    result = EXIT_FAILURE;

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required2 (struct gengetopt_args_info *args_info, const char *prog_name, const char *additional_error)
{
  int error = 0;
  FIX_UNUSED (additional_error);

  /* checks for required options */
  if (! args_info->secret_given)
    {
      fprintf (stderr, "%s: '--secret' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->keys_given)
    {
      fprintf (stderr, "%s: '--keys' ('-k') option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (args_info->actions_group_counter == 0)
    {
      fprintf (stderr, "%s: %d options of group actions were given. One is required%s.\n", prog_name, args_info->actions_group_counter, (additional_error ? additional_error : ""));
      error = 1;
    }
  

  /* checks for dependences among options */
  if (args_info->number_given && ! args_info->distribute_given)
    {
      fprintf (stderr, "%s: '--number' ('-n') option depends on option 'distribute'%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }

  return error;
}


static char *package_name = 0;

/**
 * @brief updates an option
 * @param field the generic pointer to the field to update
 * @param orig_field the pointer to the orig field
 * @param field_given the pointer to the number of occurrence of this option
 * @param prev_given the pointer to the number of occurrence already seen
 * @param value the argument for this option (if null no arg was specified)
 * @param possible_values the possible values for this option (if specified)
 * @param default_value the default value (in case the option only accepts fixed values)
 * @param arg_type the type of this option
 * @param check_ambiguity @see cmdline_parser_params.check_ambiguity
 * @param override @see cmdline_parser_params.override
 * @param no_free whether to free a possible previous value
 * @param multiple_option whether this is a multiple option
 * @param long_opt the corresponding long option
 * @param short_opt the corresponding short option (or '-' if none)
 * @param additional_error possible further error specification
 */
static
int update_arg(void *field, char **orig_field,
               unsigned int *field_given, unsigned int *prev_given, 
               char *value, const char *possible_values[],
               const char *default_value,
               cmdline_parser_arg_type arg_type,
               int check_ambiguity, int override,
               int no_free, int multiple_option,
               const char *long_opt, char short_opt,
               const char *additional_error)
{
  char *stop_char = 0;
  const char *val = value;
  int found;
  char **string_field;
  FIX_UNUSED (field);

  stop_char = 0;
  found = 0;

  if (!multiple_option && prev_given && (*prev_given || (check_ambiguity && *field_given)))
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: `--%s' (`-%c') option given more than once%s\n", 
               package_name, long_opt, short_opt,
               (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: `--%s' option given more than once%s\n", 
               package_name, long_opt,
               (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  if (possible_values && (found = check_possible_values((value ? value : default_value), possible_values)) < 0)
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s' (`-%c')%s\n", 
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt, short_opt,
          (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s'%s\n", 
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt,
          (additional_error ? additional_error : ""));
      return 1; /* failure */
    }
    
  if (field_given && *field_given && ! override)
    return 0;
  if (prev_given)
    (*prev_given)++;
  if (field_given)
    (*field_given)++;
  if (possible_values)
    val = possible_values[found];

  switch(arg_type) {
  case ARG_INT:
    if (val) *((int *)field) = strtol (val, &stop_char, 0);
    break;
  case ARG_STRING:
    if (val) {
      string_field = (char **)field;
      if (!no_free && *string_field)
        free (*string_field); /* free previous string */
      *string_field = gengetopt_strdup (val);
    }
    break;
  default:
    break;
  };

  /* check numeric conversion */
  switch(arg_type) {
  case ARG_INT:
    if (val && !(stop_char && *stop_char == '\0')) {
      fprintf(stderr, "%s: invalid numeric value: %s\n", package_name, val);
      return 1; /* failure */
    }
    break;
  default:
    ;
  };

  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
    break;
  default:
    if (value && orig_field) {
      if (no_free) {
        *orig_field = value;
      } else {
        if (*orig_field)
          free (*orig_field); /* free previous string */
        *orig_field = gengetopt_strdup (value);
      }
    }
  };

  return 0; /* OK */
}


int
cmdline_parser_internal (
  int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error = 0;
  struct gengetopt_args_info local_args_info;
  
  int override;
  int initialize;
  int check_required;
  int check_ambiguity;
  
  package_name = argv[0];
  
  override = params->override;
  initialize = params->initialize;
  check_required = params->check_required;
  check_ambiguity = params->check_ambiguity;

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = params->print_errors;
  optopt = '?';

  while (1)
    {
      int option_index = 0;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "detailed-help",	0, NULL, 0 },
        { "version",	0, NULL, 'V' },
        { "distribute",	0, NULL, 'd' },
        { "recovery",	0, NULL, 'r' },
        { "secret",	1, NULL, 0 },
        { "keys",	1, NULL, 'k' },
        { "number",	1, NULL, 'n' },
        { "dir",	1, NULL, 0 },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "hVdrk:n:", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          cmdline_parser_print_help ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          cmdline_parser_print_version ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'd':	/* Distributes the secret.  */
        
          if (args_info->actions_group_counter && override)
            reset_group_actions (args_info);
          args_info->actions_group_counter += 1;
        
          if (update_arg( 0 , 
               0 , &(args_info->distribute_given),
              &(local_args_info.distribute_given), optarg, 0, 0, ARG_NO,
              check_ambiguity, override, 0, 0,
              "distribute", 'd',
              additional_error))
            goto failure;
        
          break;
        case 'r':	/* Recovers the secret.  */
        
          if (args_info->actions_group_counter && override)
            reset_group_actions (args_info);
          args_info->actions_group_counter += 1;
        
          if (update_arg( 0 , 
               0 , &(args_info->recovery_given),
              &(local_args_info.recovery_given), optarg, 0, 0, ARG_NO,
              check_ambiguity, override, 0, 0,
              "recovery", 'r',
              additional_error))
            goto failure;
        
          break;
        case 'k':	/* Number of keys to recover the secret.  */
        
        
          if (update_arg( (void *)&(args_info->keys_arg), 
               &(args_info->keys_orig), &(args_info->keys_given),
              &(local_args_info.keys_given), optarg, cmdline_parser_keys_values, 0, ARG_INT,
              check_ambiguity, override, 0, 0,
              "keys", 'k',
              additional_error))
            goto failure;
        
          break;
        case 'n':	/* Total number of shadows where the secret will be distributed.  */
        
        
          if (update_arg( (void *)&(args_info->number_arg), 
               &(args_info->number_orig), &(args_info->number_given),
              &(local_args_info.number_given), optarg, cmdline_parser_number_values, 0, ARG_INT,
              check_ambiguity, override, 0, 0,
              "number", 'n',
              additional_error))
            goto failure;
        
          break;

        case 0:	/* Long option with no short option */
          if (strcmp (long_options[option_index].name, "detailed-help") == 0) {
            cmdline_parser_print_detailed_help ();
            cmdline_parser_free (&local_args_info);
            exit (EXIT_SUCCESS);
          }

          /* Image path of a .bmp image.  */
          if (strcmp (long_options[option_index].name, "secret") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->secret_arg), 
                 &(args_info->secret_orig), &(args_info->secret_given),
                &(local_args_info.secret_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "secret", '-',
                additional_error))
              goto failure;
          
          }
          /* Directory where the images will be placed.  */
          else if (strcmp (long_options[option_index].name, "dir") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->dir_arg), 
                 &(args_info->dir_orig), &(args_info->dir_given),
                &(local_args_info.dir_given), optarg, 0, "./", ARG_STRING,
                check_ambiguity, override, 0, 0,
                "dir", '-',
                additional_error))
              goto failure;
          
          }
          
          break;
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */

  if (args_info->actions_group_counter > 1)
    {
      fprintf (stderr, "%s: %d options of group actions were given. One is required%s.\n", argv[0], args_info->actions_group_counter, (additional_error ? additional_error : ""));
      error = 1;
    }
  


  if (check_required)
    {
      error += cmdline_parser_required2 (args_info, argv[0], additional_error);
    }

  cmdline_parser_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  return 0;

failure:
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}
